/*
 * Copyright (C) 2010 The Android Open Source Project
 * Copyright (C) 2016 Jonathan Jason Dennis [Meticulus]
 *				theonejohnnyd@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <hardware/hardware.h>
#include <utils/ThreadDefs.h>
#include <utils/Timers.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/resource.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ioctl.h>
#define LOG_TAG "Met-Dev Hisi HWC"
#include <cutils/log.h>
#include <cutils/atomic.h>

#include <hardware/hwcomposer.h>

#include <EGL/egl.h>

#include "hisi_dss.h"
/*****************************************************************************/
#define FAKE_VSYNC

#define NSEC_PER_SEC    1000000000L
#define NSEC_PER_MSEC   1000000L

#ifdef FAKE_VSYNC
#ifndef REFRESH_RATE
#define REFRESH_RATE (60.0)
#endif // REFRESH_RATE
#define REFRESH_PERIOD ((int64_t)(NSEC_PER_SEC / REFRESH_RATE))

#endif // FAKE_VSYNC

#define FB0_FILE "/dev/graphics/fb0"
#define FB1_FILE "/dev/graphics/fb1"
#define FB2_FILE "/dev/graphics/fb2"
#define TIMESTAMP_FILE "/sys/devices/virtual/graphics/fb0/vsync_timestamp"

//#define DEBUG

#ifdef DEBUG
#define DEBUG_LOG(x...) ALOGD(x)
#else
#define DEBUG_LOG(x...) do {} while(0)
#endif

struct fb_ctx_t {
    int id;
    int available;
    int fd;
    int vsyncfd;
    int vsync_on;
    int vsync_stop;
    int vthread_running;
    int fake_vsync;
    pthread_t vthread;
    hwc_procs_t const *hwc_procs;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

struct hwc_context_t {
    hwc_composer_device_1_t device;
    /* our private state goes below here */
    fb_ctx_t disp[3];
};

static void write_string(const char * path, const char * value) {
    int fd = open(path, O_WRONLY);
	if(!fd) { ALOGE("Unable to open to %s", path); return;}

	ssize_t bytes_written = write(fd, value, strlen(value));

	if (bytes_written < 1 || bytes_written < strlen(value)) {
		ALOGE("Unable to write to %s : %d",path, bytes_written);
	}

    close(fd);
}

static int hwc_device_open(const struct hw_module_t* module, const char* name,
        struct hw_device_t** device);

static struct hw_module_methods_t hwc_module_methods = {
    .open = hwc_device_open
};

hwc_module_t HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .version_major = 1,
        .version_minor = 0,
        .id = HWC_HARDWARE_MODULE_ID,
        .name = "Met-Dev Hisi HWComposer",
        .author = "Meticulus Development",
        .methods = &hwc_module_methods,
    }
};

/*****************************************************************************/

static void dump_layer(hwc_layer_1_t const* l) {
    DEBUG_LOG("\ttype=%d, flags=%08x, handle=%p, tr=%02x, blend=%04x, {%d,%d,%d,%d}, {%d,%d,%d,%d}",
            l->compositionType, l->flags, l->handle, l->transform, l->blending,
            l->sourceCrop.left,
            l->sourceCrop.top,
            l->sourceCrop.right,
            l->sourceCrop.bottom,
            l->displayFrame.left,
            l->displayFrame.top,
            l->displayFrame.right,
            l->displayFrame.bottom);
}

static int hwc_prepare(hwc_composer_device_1_t *dev,
        size_t numDisplays, hwc_display_contents_1_t** displays) {
    for(size_t j=0; j<numDisplays; j++) {
	if (displays && (displays[j]->flags & HWC_GEOMETRY_CHANGED)) {
	    for (size_t i=0 ; i<displays[j]->numHwLayers ; i++) {
		displays[j]->hwLayers[i].compositionType = HWC_FRAMEBUFFER;
            }
	}
    }
    return 0;
}

static int hwc_set(hwc_composer_device_1_t *dev,
        size_t numDisplays, hwc_display_contents_1_t** displays)
{
    /*for (size_t i=0 ; i<list->numHwLayers ; i++) {
        dump_layer(&list->hwLayers[i]);
    }*/
    for(size_t j=0; j<numDisplays; j++) {
	EGLBoolean sucess = eglSwapBuffers((EGLDisplay)displays[j]->dpy,
		(EGLSurface)displays[j]->sur);
	if (!sucess) {
	    return HWC_EGL_ERROR;
	}
    }
    return 0;
}

static void * vsync_thread(void * arg) {
   setpriority(PRIO_PROCESS, 0, HAL_PRIORITY_URGENT_DISPLAY +
                android::PRIORITY_MORE_FAVORABLE);
   fb_ctx_t *fb = (fb_ctx_t *) arg;
   DEBUG_LOG("vsync thread enter id = %d fake = %d", fb->id, fb->fake_vsync);
   fb->vthread_running = 1;
   int retval = -1;
   int64_t timestamp = 0;
   char read_result[20];
   if(fb->fake_vsync) {
	while(true) {
	    if(!fb->vsync_on) {
		DEBUG_LOG("vsync thread sleeping id = %d fake = 1", fb->id);
		while(!fb->vsync_on && !fb->vsync_stop)
		    pthread_cond_wait(&fb->cond,&fb->mutex);
		DEBUG_LOG("vsync thread woke up id = %d fake = 1", fb->id);
		if(fb->vsync_stop)
		    break;
		if(!fb->vsync_on)
		    continue;
	    }
	    timestamp = systemTime();
	    fb->hwc_procs->vsync(fb->hwc_procs,fb->id,timestamp);
	    usleep(16666);
	}
   } else {
	while(true) {
	    if(!fb->vsync_on) {
		DEBUG_LOG("vsync thread sleeping id = %d fake = 0", fb->id);
		while(!fb->vsync_on && !fb->vsync_stop)
		    pthread_cond_wait(&fb->cond,&fb->mutex);
		DEBUG_LOG("vsync thread woke up id = %d fake = 0", fb->id);
		if(fb->vsync_stop)
		    break;
		if(!fb->vsync_on)
		    continue;
	    }
	    if(pread(fb->vsyncfd,read_result,20,0)) {
		timestamp = atol(read_result);
		fb->hwc_procs->vsync(fb->hwc_procs, fb->id, timestamp);
		usleep(16500);
	    } else { goto error; }
       }
   }

   retval = 0;
error:
   fb->vthread_running = 0;
   DEBUG_LOG("vsync thread exit");
   return &retval; 

}

static void signal_vsync_thread(fb_ctx_t *fb) {
    if(fb->vthread_running) {
	pthread_mutex_lock(&fb->mutex);
	pthread_cond_signal(&fb->cond);
	pthread_mutex_unlock(&fb->mutex);
    }
}

static void start_vsync_thread(fb_ctx_t *fb) {

    if(!fb->fake_vsync)
	ioctl(fb->fd,HISIFB_VSYNC_CTRL, &fb->vsync_on);

    if(!fb->vthread_running) {
	pthread_create(&fb->vthread,NULL,&vsync_thread, fb);
    } else {
	signal_vsync_thread(fb);
    }
}

static int hwc_event_control (struct hwc_composer_device_1* dev, int disp,
            int event, int enabled) {
    /*if(!enabled) return 0;
    if(event == HWC_EVENT_VSYNC) {
	struct hwc_context_t *context = (hwc_context_t *)dev;

	    if(!context->disp[disp].available)
		return -EINVAL;
	    context->disp[disp].vsync_on = enabled;
	    start_vsync_thread(&context->disp[disp]);
    }*/
    return 0;

}

static int hwc_blank(struct hwc_composer_device_1* dev, int disp, int blank) {
    int ret = -1;
    int fd = -1;
    struct hwc_context_t *context = (hwc_context_t *)dev;

    if(context->disp[disp].available) {
	fd = context->disp[disp].fd;
	context->disp[disp].vsync_stop = blank;
	context->disp[disp].vsync_on = blank ? 0 : 1;
	signal_vsync_thread(&context->disp[disp]);
    } else
	return -EINVAL;


    if(fd > 0) {
        ret = ioctl(fd, FBIOBLANK, blank ? FB_BLANK_NORMAL : FB_BLANK_UNBLANK);
        if(ret)
	    ALOGE("Could not %s framebuffer! on disp %d", blank ? "blank" : "unblank?", disp);

    } else {
	ALOGE("Meticulus: somehow the fd on %d was invalid while %s ?", disp, blank ? "banking" : "unblanking");
	return -EINVAL;
    }


    DEBUG_LOG("blank called %d",blank);
    return ret;
}

static void register_procs(struct hwc_composer_device_1* dev,
            hwc_procs_t const* procs) {
    struct hwc_context_t *context = (hwc_context_t *)dev;

    context->disp[HWC_DISPLAY_PRIMARY].hwc_procs = procs;
    context->disp[HWC_DISPLAY_EXTERNAL].hwc_procs = procs;
    context->disp[HWC_DISPLAY_VIRTUAL].hwc_procs = procs;
    DEBUG_LOG("procs registered");
}

static int query(struct hwc_composer_device_1* dev, int what, int* value) {
    DEBUG_LOG("query %d %d",what,*value);

	int retval = 0;
	switch (what) {
	    case HWC_BACKGROUND_LAYER_SUPPORTED:
		retval =0;
		value = &retval;
		break;
	    case HWC_VSYNC_PERIOD:
		retval = REFRESH_PERIOD;	
		value = &retval;
		break;
	    default:
		ALOGE("Unknown query %d",what);
		break;
    }
    return retval;
}

static int hwc_device_close(struct hw_device_t *dev)
{
    struct hwc_context_t* ctx = (struct hwc_context_t*)dev;
    if (ctx) {
        free(ctx);
    }
    return 0;
}

/*****************************************************************************/

static int hwc_device_open(const struct hw_module_t* module, const char* name,
        struct hw_device_t** device)
{
    int status = 0;
    if (!strcmp(name, HWC_HARDWARE_COMPOSER)) {
        struct hwc_context_t *dev;
        dev = (hwc_context_t*)malloc(sizeof(*dev));

        /* initialize our state here */
        memset(dev, 0, sizeof(*dev));

        /* initialize the procs */
        dev->device.common.tag = HARDWARE_DEVICE_TAG;
        dev->device.common.version = HWC_DEVICE_API_VERSION_1_0;
        dev->device.common.module = const_cast<hw_module_t*>(module);
        dev->device.common.close = hwc_device_close;

        dev->device.prepare = hwc_prepare;
        dev->device.set = hwc_set;
        dev->device.blank = hwc_blank;
        dev->device.eventControl = hwc_event_control;
        dev->device.registerProcs = register_procs;
        dev->device.query = query;
	/* init primary display */
	dev->disp[HWC_DISPLAY_PRIMARY].vthread_running = 0;
	dev->disp[HWC_DISPLAY_PRIMARY].vsync_on = 0;
	dev->disp[HWC_DISPLAY_PRIMARY].vsync_stop = 0;
	dev->disp[HWC_DISPLAY_PRIMARY].fake_vsync = 0;
	dev->disp[HWC_DISPLAY_PRIMARY].id = HWC_DISPLAY_PRIMARY;
        dev->disp[HWC_DISPLAY_PRIMARY].mutex = PTHREAD_MUTEX_INITIALIZER;
        dev->disp[HWC_DISPLAY_PRIMARY].cond = PTHREAD_COND_INITIALIZER;
	dev->disp[HWC_DISPLAY_PRIMARY].fd = open (FB0_FILE, O_WRONLY);
	if(dev->disp[HWC_DISPLAY_PRIMARY].fd < 0) {
	    ALOGE("Could not open fb0 file!");
	    status = -EINVAL;
   	}
	dev->disp[HWC_DISPLAY_PRIMARY].available = 1;
	dev->disp[HWC_DISPLAY_PRIMARY].vsyncfd = open(TIMESTAMP_FILE, O_RDONLY);
	if(dev->disp[HWC_DISPLAY_PRIMARY].vsyncfd < 0) {
	    ALOGW("Using fake vsync on primary...");
	    dev->disp[HWC_DISPLAY_PRIMARY].fake_vsync = 1;
	}
	/* init external physical display */
	dev->disp[HWC_DISPLAY_EXTERNAL].available = 1;
	dev->disp[HWC_DISPLAY_EXTERNAL].id = HWC_DISPLAY_EXTERNAL;
        dev->disp[HWC_DISPLAY_EXTERNAL].mutex = PTHREAD_MUTEX_INITIALIZER;
        dev->disp[HWC_DISPLAY_EXTERNAL].cond = PTHREAD_COND_INITIALIZER;
	dev->disp[HWC_DISPLAY_EXTERNAL].fd = open (FB1_FILE, O_WRONLY);
	if(dev->disp[HWC_DISPLAY_EXTERNAL].fd < 0) {
	    ALOGW("Could not open fb1 file!");
	    ALOGW("External physicals display will be unavailable.");
	    dev->disp[HWC_DISPLAY_EXTERNAL].available = 0;
	}
	dev->disp[HWC_DISPLAY_EXTERNAL].fake_vsync = 1;
	dev->disp[HWC_DISPLAY_EXTERNAL].vsync_on = 0;
	dev->disp[HWC_DISPLAY_EXTERNAL].vsync_stop = 0;
	/* init virtual displays */
	dev->disp[HWC_DISPLAY_VIRTUAL].available = 1;
	dev->disp[HWC_DISPLAY_VIRTUAL].id = HWC_DISPLAY_VIRTUAL;
        dev->disp[HWC_DISPLAY_VIRTUAL].mutex = PTHREAD_MUTEX_INITIALIZER;
        dev->disp[HWC_DISPLAY_VIRTUAL].cond = PTHREAD_COND_INITIALIZER;
	dev->disp[HWC_DISPLAY_VIRTUAL].fd = open (FB2_FILE, O_WRONLY);
	if(dev->disp[HWC_DISPLAY_VIRTUAL].fd < 0) {
	    ALOGE("Could not open fb2 file!");
	    ALOGW("Virtual displays will be unavailable.");
	    dev->disp[HWC_DISPLAY_VIRTUAL].available = 0;
   	}
	dev->disp[HWC_DISPLAY_VIRTUAL].fake_vsync = 1;
	dev->disp[HWC_DISPLAY_VIRTUAL].vsync_stop = 0;
	dev->disp[HWC_DISPLAY_VIRTUAL].vsync_on = 0;
        *device = &dev->device.common;
    }
    return status;
}

/*
 * Copyright (C) 2020 The LineageOS Project
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

#define LOG_TAG "android.hardware.light@2.0-service.hisi"

#include <android-base/logging.h>
#include <hidl/HidlTransportSupport.h>
#include <utils/Errors.h>

#include "Light.h"

// libhwbinder:
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

// Generated HIDL files
using android::hardware::light::V2_0::ILight;
using android::hardware::light::V2_0::implementation::Light;

const static std::string kLcdBacklightPath = "/sys/class/leds/lcd_backlight0/brightness";
const static std::string kLcdMaxBacklightPath = "/sys/class/leds/lcd_backlight0/max_brightness";
const static std::string kRedLedPath = "/sys/class/leds/red/brightness";
const static std::string kGreenLedPath = "/sys/class/leds/green/brightness";
const static std::string kBlueLedPath = "/sys/class/leds/blue/brightness";
const static std::string kRedDelayOffPath = "/sys/class/leds/red/delay_off";
const static std::string kGreenDelayOffPath = "/sys/class/leds/green/delay_off";
const static std::string kBlueDelayOffPath = "/sys/class/leds/blue/delay_off";
const static std::string kRedLedDelayOnPath = "/sys/class/leds/red/delay_on";
const static std::string kGreenLedDelayOnPath = "/sys/class/leds/green/delay_on";
const static std::string kBlueLedDelayOnPath = "/sys/class/leds/blue/delay_on";

int main() {
    uint32_t lcdMaxBrightness = 255;

    std::ofstream lcdBacklight(kLcdBacklightPath);
    if (!lcdBacklight) {
        LOG(ERROR) << "Failed to open " << kLcdBacklightPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    }

    std::ifstream lcdMaxBacklight(kLcdMaxBacklightPath);
    if (!lcdMaxBacklight) {
        LOG(ERROR) << "Failed to open " << kLcdMaxBacklightPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return -errno;
    } else {
        lcdMaxBacklight >> lcdMaxBrightness;
    }

    std::ofstream redLed(kRedLedPath);
    if (!redLed) {
        LOG(ERROR) << "Failed to open " << kRedLedPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
    }

    std::ofstream greenLed(kGreenLedPath);
    if (!greenLed) {
        LOG(ERROR) << "Failed to open " << kGreenLedPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
    }

    std::ofstream blueLed(kBlueLedPath);
    if (!blueLed) {
        LOG(ERROR) << "Failed to open " << kBlueLedPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
    }

    std::ofstream redDelayOff(kRedDelayOffPath);
    if (!redDelayOff) {
        LOG(ERROR) << "Failed to open " << kRedDelayOffPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
    }

    std::ofstream greenDelayOff(kGreenDelayOffPath);
    if (!greenDelayOff) {
        LOG(ERROR) << "Failed to open " << kGreenDelayOffPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
    }

    std::ofstream blueDelayOff(kBlueDelayOffPath);
    if (!blueDelayOff) {
        LOG(ERROR) << "Failed to open " << kBlueDelayOffPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
    }

    std::ofstream redDelayOn(kRedLedDelayOnPath);
    if (!redDelayOn) {
        LOG(ERROR) << "Failed to open " << kRedLedDelayOnPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
    }

    std::ofstream greenDelayOn(kGreenLedDelayOnPath);
    if (!greenDelayOn) {
        LOG(ERROR) << "Failed to open " << kGreenLedDelayOnPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
    }

    std::ofstream blueDelayOn(kBlueLedDelayOnPath);
    if (!blueDelayOff) {
        LOG(ERROR) << "Failed to open " << kBlueLedDelayOnPath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
    }

    android::sp<ILight> service = new Light(
            {std::move(lcdBacklight), lcdMaxBrightness},
            std::move(redLed), std::move(greenLed), std::move(blueLed),
            std::move(redDelayOff), std::move(greenDelayOff), std::move(blueDelayOff),
            std::move(redDelayOn), std::move(greenDelayOn), std::move(blueDelayOn));

    configureRpcThreadpool(1, true);

    android::status_t status = service->registerAsService();

    if (status != android::OK) {
        LOG(ERROR) << "Cannot register Light HAL service";
        return 1;
    }

    LOG(INFO) << "Light HAL Ready.";
    joinRpcThreadpool();
    // Under normal cases, execution will not reach this line.
    LOG(ERROR) << "Light HAL failed to join thread pool.";
    return 1;
}

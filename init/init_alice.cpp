/*
   Copyright (c) 2017, The Lineage OS Project
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "vendor_init.h"
#include "property_service.h"

std::string replaceStrChar(std::string str, const std::string& replace, char ch) {

    std::size_t found = str.find_first_of(replace);

    while (found != std::string::npos) {
    	str[found] = ch;
    	found = str.find_first_of(replace, found+1);
    }

    return str;
}

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void vendor_load_properties() {

    int i;
    std::ifstream fin;
    std::string buf, modem;

    fin.open("/sys/firmware/devicetree/base/boardinfo/normal_product_name");
    if (!fin) {
    	property_override("ro.product.model", "ALICE");
    } else {
        std::string model;
        fin >> model;
        property_override("ro.product.model", model.data());
    }
    fin.close();

    property_override("ro.build.description", "ALE-L21-user 6.0 HuaweiALE-L21 C432B596 release-keys");
    property_override("ro.build.fingerprint", "Huawei/ALE-L21/hwALE-H:6.0/HuaweiALE-L21/C432B596:user/release-keys");
    
    fin.open("/proc/cmdline");
    while (std::getline(fin, buf, ' '))
        if (buf.find("productid") != std::string::npos)
            break;
    fin.close();

    for (i = 0; i < buf.size(); i++) {
    	if (i > 9) {
       		modem.push_back(buf[i]);
    	}
    }

    modem = replaceStrChar(modem, "x", 'X');
    modem = replaceStrChar(modem, "a", 'A');
    modem = replaceStrChar(modem, "b", 'B');
    modem = replaceStrChar(modem, "c", 'C');
    modem = replaceStrChar(modem, "d", 'D');
    modem = replaceStrChar(modem, "e", 'E');
    modem = replaceStrChar(modem, "f", 'F');

    if (strcmp(modem.c_str(), "0X0000002B") == 0) {
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.multi.rild", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X00000049") == 0) {
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib/libbalong-ril.so");
        property_override("rild.libpath1", "/vendor/lib/libbalong-ril.so");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.multi.rild", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X00000035") == 0) {
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib/libbalong-ril.so");
        property_override("rild.libpath1", "/vendor/lib/libbalong-ril.so");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.multi.rild", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DF51180") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_device_mode", "clg_mode");
        property_override("rild.libargs", "-m modem1");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath2", "/vendor/lib64/libbalong-ril-1.so");
        property_override("ro.telephony.default_network", "4");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem0");
        property_override("rild.libpath", "/vendor/lib64/libvia-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB51580") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_device_mode", "clg_mode");
        property_override("rild.libargs", "-m modem1");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "4");
        property_override("rild.libpath2", "/vendor/lib64/libbalong-ril-1.so");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem0");
        property_override("rild.libpath", "/vendor/lib64/libvia-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DF50180") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_device_mode", "clg_mode");
        property_override("rild.libargs", "-m modem1");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "4");
        property_override("rild.libpath2", "/vendor/lib64/libbalong-ril-1.so");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem0");
        property_override("rild.libpath", "/vendor/lib64/libvia-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB50580") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_device_mode", "clg_mode");
        property_override("rild.libargs", "-m modem1");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "4");
        property_override("rild.libpath2", "/vendor/lib64/libbalong-ril-1.so");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem0");
        property_override("rild.libpath", "/vendor/lib64/libvia-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD50500") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD51500") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD52100") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB50500") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB51500") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB51518") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54100") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB52500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB52519") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB52514") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB52515") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB53500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB00500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB01500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD51D00") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD51D0B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DF53D00") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3D350500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "0");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3D300500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.telephony.default_network", "0");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3D351500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "0");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB02100") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54514") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54515") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5454F") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5456A") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54555") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54559") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D00") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD52500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD5250B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DF50500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3D351D00") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "0");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD52900") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DF51180") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_device_mode", "clg_mode");
        property_override("rild.libargs", "-m modem1");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "4");
        property_override("rild.libpath2", "/vendor/lib64/libbalong-ril-1.so");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem0");
        property_override("rild.libpath", "/vendor/lib64/libvia-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB51580") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_device_mode", "clg_mode");
        property_override("rild.libargs", "-m modem1");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "4");
        property_override("rild.libpath2", "/vendor/lib64/libbalong-ril-1.so");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem0");
        property_override("rild.libpath", "/vendor/lib64/libvia-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DF50180") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_device_mode", "clg_mode");
        property_override("rild.libargs", "-m modem1");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "4");
        property_override("rild.libpath2", "/vendor/lib64/libbalong-ril-1.so");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem0");
        property_override("rild.libpath", "/vendor/lib64/libvia-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB50580") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_device_mode", "clg_mode");
        property_override("rild.libargs", "-m modem1");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "4");
        property_override("rild.libpath2", "/vendor/lib64/libbalong-ril-1.so");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem0");
        property_override("rild.libpath", "/vendor/lib64/libvia-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD50500") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD51500") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD52100") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB50500") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB51500") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB51518") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54100") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB52500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5251A") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB52514") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB52515") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB53500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB00500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB01500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD51D00") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD51D0B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DF53D00") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3D350500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "0");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3D35051A") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "0");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3D300500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.telephony.default_network", "0");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3D351500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "0");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB02100") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB0215A") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB02160") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB02166") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54514") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54515") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5456A") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5454F") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5451B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5451C") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5451D") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5451E") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5451F") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54520") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54521") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54522") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54523") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54524") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54525") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54526") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54527") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54528") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54529") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5452A") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5452B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5452C") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5452D") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54540") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54541") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54542") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54543") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54544") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54545") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54546") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54547") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54534") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54535") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54536") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54537") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54538") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54539") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5453A") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5453B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5453C") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5453D") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5453E") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5453F") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54530") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54549") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5454A") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5454D") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5452E") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54555") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54559") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54553") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54557") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54558") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54550") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54551") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54552") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54554") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5451A") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D00") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D48") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D4B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D56") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D5D") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D4C") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D5F") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D1A") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD52500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD5250B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DF50500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3D351D00") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "0");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD52900") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB08D00") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB08D0D") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB08D48") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB08D4C") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB08D19") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB08D5F") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB08D4B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB08D18") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB08D4E") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB08D5C") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB08D6F") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB08D42") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59100") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59115") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59114") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59117") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5911A") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59173") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59179") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5916A") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5914E") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59162") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5917A") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59163") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59161") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5917D") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59165") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5913E") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B95");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59502") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B95");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5950B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B95");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59503") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B95");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59509") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B95");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59D00") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59D4E") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB59D4C") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5A500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5A54B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD58500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B95");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD5850B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B95");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD5A900") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B95");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD5A90B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B95");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD59900") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD5990D") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD59948") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD5994C") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD59919") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD5995F") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD5994B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD59918") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD59942") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD5996F") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD5994E") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD5995C") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DF58900") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B95");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DF58902") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B95");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DF5890B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B95");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DF58903") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B95");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DF58909") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B95");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3D35A100") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "0");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3D35A115") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "0");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3D35A117") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "0");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD5AD00") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B95");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DD5B100") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B95");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    } // start Honor 4x/4c
    else if (strcmp(modem.c_str(), "0X0000002B") == 0) {
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.multi.rild", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X00000049") == 0) {
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib/libbalong-ril.so");
        property_override("rild.libpath1", "/vendor/lib/libbalong-ril.so");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.multi.rild", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X00000035") == 0) {
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath", "/vendor/lib/libbalong-ril.so");
        property_override("rild.libpath1", "/vendor/lib/libbalong-ril.so");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.multi.rild", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DF51180") == 0) {
        property_override("rild.libargs1", "-m modem0");
        property_override("rild.libpath2", "/vendor/lib64/libbalong-ril-1.so");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem1");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.config.hw_device_mode", "clg_mode");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libvia-ril.so");
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.telephony.default_network", "4");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB51580") == 0) {
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.config.hw_device_mode", "clg_mode");
        property_override("rild.libpath", "/vendor/lib64/libvia-ril.so");
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.telephony.default_network", "4");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem0");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libpath2", "/vendor/lib64/libbalong-ril-1.so");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem1");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DF50180") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.config.hw_device_mode", "clg_mode");
        property_override("rild.libpath", "/vendor/lib64/libvia-ril.so");
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.telephony.default_network", "4");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem1");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs1", "-m modem0");
        property_override("rild.libpath2", "/vendor/lib64/libbalong-ril-1.so");
        property_override("persist.dsds.enabled", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB50580") == 0) {
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem1");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libargs1", "-m modem0");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libpath2", "/vendor/lib64/libbalong-ril-1.so");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.config.hw_device_mode", "clg_mode");
        property_override("rild.libpath", "/vendor/lib64/libvia-ril.so");
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.telephony.default_network", "4");
    }
    else if (strcmp(modem.c_str(), "0X3DD50500") == 0) {
        property_override("persist.radio.modem.cap", "89994");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
    }
    else if (strcmp(modem.c_str(), "0X3DD51500") == 0) {
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.radio.modem.cap", "89994");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.telephony.default_network", "9");
    }
    else if (strcmp(modem.c_str(), "0X3DD52100") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
    }
    else if (strcmp(modem.c_str(), "0X3DB50500") == 0) {
        property_override("persist.radio.modem.cap", "89994");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB51500") == 0) {
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "true");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("persist.radio.modem.cap", "89994");
    }
    else if (strcmp(modem.c_str(), "0X3DB51518") == 0) {
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB54100") == 0) {
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "true");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("persist.radio.modem.cap", "89994");
    }
    else if (strcmp(modem.c_str(), "0X3DB52500") == 0) {
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB52519") == 0) {
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB52514") == 0) {
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB52515") == 0) {
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB53500") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB00500") == 0) {
        property_override("persist.dsds.enabled", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB01500") == 0) {
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09994");
    }
    else if (strcmp(modem.c_str(), "0X3DD51D00") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DD51D0B") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DF53D00") == 0) {
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3D350500") == 0) {
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "0");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3D300500") == 0) {
        property_override("persist.dsds.enabled", "false");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "0");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3D351500") == 0) {
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "0");
        property_override("ro.config.hw_dsda", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB02100") == 0) {
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
    }
    else if (strcmp(modem.c_str(), "0X3DB02168") == 0) {
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54500") == 0) {
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54514") == 0) {
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
    }
    else if (strcmp(modem.c_str(), "0X3DB54515") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB54517") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB5454F") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DB5456A") == 0) {
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
    }
    else if (strcmp(modem.c_str(), "0X3DB54555") == 0) {
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
    }
    else if (strcmp(modem.c_str(), "0X3DB54559") == 0) {
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D00") == 0) {
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
    }
    else if (strcmp(modem.c_str(), "0X3DD52500") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
    }
    else if (strcmp(modem.c_str(), "0X3DD5250B") == 0) {
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DF50500") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
    }
    else if (strcmp(modem.c_str(), "0X3D351D00") == 0) {
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "0");
        property_override("ro.config.hw_dsda", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DD52900") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DF51180") == 0) {
        property_override("rild.libargs", "-m modem1");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libpath2", "/vendor/lib64/libbalong-ril-1.so");
        property_override("rild.libargs1", "-m modem0");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libvia-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.config.hw_device_mode", "clg_mode");
        property_override("ro.telephony.default_network", "4");
        property_override("ro.config.hw_dsda", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB51580") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.telephony.default_network", "4");
        property_override("ro.config.hw_device_mode", "clg_mode");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libvia-ril.so");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem0");
        property_override("rild.libpath2", "/vendor/lib64/libbalong-ril-1.so");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DF50180") == 0) {
        property_override("rild.libpath2", "/vendor/lib64/libbalong-ril-1.so");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem0");
        property_override("rild.libargs", "-m modem1");
        property_override("ro.multi.rild", "false");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libpath", "/vendor/lib64/libvia-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.config.hw_device_mode", "clg_mode");
        property_override("ro.telephony.default_network", "4");
        property_override("ro.config.hw_dsda", "true");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB50580") == 0) {
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libpath2", "/vendor/lib64/libbalong-ril-1.so");
        property_override("rild.libargs1", "-m modem0");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem1");
        property_override("ro.multi.rild", "false");
        property_override("ro.telephony.default_network", "4");
        property_override("ro.config.hw_dsda", "true");
        property_override("rild.libpath", "/vendor/lib64/libvia-ril.so");
        property_override("ro.config.hw_device_mode", "clg_mode");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DD50500") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
    }
    else if (strcmp(modem.c_str(), "0X3DD51500") == 0) {
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "true");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DD52100") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "89994");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DB50500") == 0) {
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
    }
    else if (strcmp(modem.c_str(), "0X3DB51500") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "true");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DB51518") == 0) {
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "true");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("persist.radio.modem.cap", "89994");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB54100") == 0) {
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "89994");
        property_override("persist.radio.multisim.config", "dsda");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
    }
    else if (strcmp(modem.c_str(), "0X3DB52500") == 0) {
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5251A") == 0) {
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB52514") == 0) {
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
    }
    else if (strcmp(modem.c_str(), "0X3DB52515") == 0) {
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB53500") == 0) {
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
    }
    else if (strcmp(modem.c_str(), "0X3DB00500") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.radio.modem.cap", "09994");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts");
        property_override("persist.dsds.enabled", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB01500") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.dsds.enabled", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DD51D00") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DD51D0B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
    }
    else if (strcmp(modem.c_str(), "0X3DF53D00") == 0) {
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3D350500") == 0) {
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3D350514") == 0) {
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "0");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3D350517") == 0) {
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.telephony.default_network", "0");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
    }
    else if (strcmp(modem.c_str(), "0X3D35051A") == 0) {
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "0");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3D350555") == 0) {
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "0");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3D300500") == 0) {
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09994");
        property_override("ro.telephony.default_network", "0");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3D351500") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "0");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB02100") == 0) {
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB0215A") == 0) {
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
    }
    else if (strcmp(modem.c_str(), "0X3DB02160") == 0) {
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
    }
    else if (strcmp(modem.c_str(), "0X3DB02166") == 0) {
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB02168") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB0211A") == 0) {
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54500") == 0) {
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB54514") == 0) {
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
    }
    else if (strcmp(modem.c_str(), "0X3DB54515") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
    }
    else if (strcmp(modem.c_str(), "0X3DB54517") == 0) {
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB5456A") == 0) {
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB5454F") == 0) {
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB5451B") == 0) {
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB5451C") == 0) {
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
    }
    else if (strcmp(modem.c_str(), "0X3DB5451D") == 0) {
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
    }
    else if (strcmp(modem.c_str(), "0X3DB5451E") == 0) {
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB5451F") == 0) {
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54520") == 0) {
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
    }
    else if (strcmp(modem.c_str(), "0X3DB54521") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54522") == 0) {
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
    }
    else if (strcmp(modem.c_str(), "0X3DB54523") == 0) {
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54524") == 0) {
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
    }
    else if (strcmp(modem.c_str(), "0X3DB54525") == 0) {
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54526") == 0) {
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
    }
    else if (strcmp(modem.c_str(), "0X3DB54527") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DB54528") == 0) {
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54529") == 0) {
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
    }
    else if (strcmp(modem.c_str(), "0X3DB5452A") == 0) {
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB5452B") == 0) {
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB5452C") == 0) {
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB5452D") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DB54540") == 0) {
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54541") == 0) {
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54542") == 0) {
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
    }
    else if (strcmp(modem.c_str(), "0X3DB54543") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DB54544") == 0) {
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54545") == 0) {
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
    }
    else if (strcmp(modem.c_str(), "0X3DB54546") == 0) {
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
    }
    else if (strcmp(modem.c_str(), "0X3DB54547") == 0) {
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54534") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54535") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54536") == 0) {
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54537") == 0) {
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54538") == 0) {
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54539") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DB5453A") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB5453B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
    }
    else if (strcmp(modem.c_str(), "0X3DB5453C") == 0) {
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB5453D") == 0) {
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB5453E") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB5453F") == 0) {
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54530") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54549") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DB5454A") == 0) {
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5454D") == 0) {
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB5452E") == 0) {
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
    }
    else if (strcmp(modem.c_str(), "0X3DB54555") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54559") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54553") == 0) {
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54557") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DB54558") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DB54550") == 0) {
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54551") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
    }
    else if (strcmp(modem.c_str(), "0X3DB54552") == 0) {
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54554") == 0) {
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB5451A") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DB5456C") == 0) {
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
    }
    else if (strcmp(modem.c_str(), "0X3DB54575") == 0) {
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
    }
    else if (strcmp(modem.c_str(), "0X3DB5457F") == 0) {
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB5455E") == 0) {
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB54579") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D00") == 0) {
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D48") == 0) {
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D4B") == 0) {
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D56") == 0) {
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "single");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D5D") == 0) {
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D4C") == 0) {
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D5F") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D1A") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D4E") == 0) {
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB54D5C") == 0) {
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09B94");
    }
    else if (strcmp(modem.c_str(), "0X3DD52500") == 0) {
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DD5250B") == 0) {
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
    }
    else if (strcmp(modem.c_str(), "0X3DF50500") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
    }
    else if (strcmp(modem.c_str(), "0X3D351D00") == 0) {
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "true");
        property_override("ro.telephony.default_network", "0");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DD52900") == 0) {
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.radio.modem.cap", "09A94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
    }
    else if (strcmp(modem.c_str(), "0X3DB08D00") == 0) {
        property_override("rild.rild1_ready_to_start", "false");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts");
        property_override("ro.multi.rild", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("persist.dsds.enabled", "false");
    }
    else if (strcmp(modem.c_str(), "0X3DB59100") == 0) {
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DB59500") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
    }
    else if (strcmp(modem.c_str(), "0X3DB59D00") == 0) {
        property_override("rild.rild1_ready_to_start", "true");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DD58500") == 0) {
        property_override("rild.libargs1", "-m modem1");
        property_override("persist.dsds.enabled", "true");
        property_override("ro.multi.rild", "true");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.hw_dsda", "false");
        property_override("ro.telephony.default_network", "9");
        property_override("rild.rild1_ready_to_start", "true");
    }
    else if (strcmp(modem.c_str(), "0X3DD59900") == 0) {
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "single");
        property_override("persist.radio.modem.cap", "09994");
        property_override("rild.rild1_ready_to_start", "false");
        property_override("persist.dsds.enabled", "false");
        property_override("ro.config.dsds_mode", "umts");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "false");
    } else if (strcmp(modem.c_str(), "0X3DF58900") == 0) {
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("ro.telephony.default_network", "9");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
    } else if (strcmp(modem.c_str(), "0X3D35A100") == 0) {
        property_override("ro.telephony.default_network", "0");
        property_override("ro.config.hw_dsda", "false");
        property_override("rild.libpath", "/vendor/lib64/libbalong-ril.so");
        property_override("persist.radio.multisim.config", "dsds");
        property_override("persist.radio.modem.cap", "09B94");
        property_override("rild.rild1_ready_to_start", "true");
        property_override("persist.dsds.enabled", "true");
        property_override("rild.libargs1", "-m modem1");
        property_override("rild.libpath1", "/vendor/lib64/libbalong-ril.so");
        property_override("ro.config.dsds_mode", "umts_gsm");
        property_override("rild.libargs", "-m modem0");
        property_override("ro.multi.rild", "true");
    }
}

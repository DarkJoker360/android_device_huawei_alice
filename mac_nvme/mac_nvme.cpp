#define LOG_TAG "mac_nvme"

#include <cstring>
#include <fstream>
#include <sstream>
#include <string>

#include <cutils/log.h>
#include <cutils/properties.h>

#define NVME_PATH "/dev/block/platform/hi_mci.0/by-name/nvme"

#define MAC_LEN 12 // mac length without ':'
#define MAC_ENTRY_MAX_LEN 28 // max length of mac entry inside nvme

#define WLAN_MAC_FILE "/data/misc/wifi/macwifi"
#define BT_MAC_FILE "/data/misc/bluedroid/macbt"

std::ifstream open_nvme() {
    std::ifstream nvme(NVME_PATH);
    if (!nvme.is_open()) {
        ALOGE("Failed to open %s!", NVME_PATH);
        exit(1);
    }

    return nvme;
}

bool is_hex(std::string str) {
    return str.find_first_not_of("0123456789ABCDEF") == std::string::npos;
}

std::string hex_to_mac(std::string hex) {
    std::stringstream ss;
    size_t split = 2;

    ss << hex.substr(0, split);

    for (size_t loc = split; loc < hex.size(); loc += split) {
        ss << ':' << hex.substr(loc, split);
    }

    return ss.str();
}

std::string read_mac(std::string mac_name) {
    char buf[1]; // TODO: improve
    std::ifstream nvme = open_nvme();
    unsigned long mac_index = 0;

    ALOGI("Searching MAC entry: %s", mac_name.c_str());

    while (!nvme.eof()) {
        nvme.read(buf, sizeof(buf));

	if (buf[0] == mac_name[mac_index]) {
            mac_index++;

            if (mac_index == (strlen(mac_name.c_str()) - 1)) {
                ALOGI("Found MAC entry: %s", mac_name.c_str());
                std::string mac;

                for(size_t i = 0; i < MAC_ENTRY_MAX_LEN; i++) {
                    char mac_buff[1];

                    nvme.read(mac_buff, sizeof(mac_buff));

                    std::string tmp_mac(1, mac_buff[0]);

                    if (is_hex(tmp_mac)) {
                        mac += tmp_mac;
                    }

                    if (strlen(mac.c_str()) == MAC_LEN) { // full mac read
                        nvme.close();

                        return hex_to_mac(mac);
                    }
                }

                ALOGW("Found a MAC entry but couldn't fully read MAC!");
                ALOGW("This is probably a bug!");
            }
        } else {
            mac_index = 0;
        }
    }

    nvme.close();

    return "00:00:00:00:00:00";
}

void write_mac(std::string file, std::string mac) {
    std::ofstream mac_out(file);

    if(!mac_out.is_open()) {
        ALOGE("Failed to open %s", file.c_str());
        exit(1);
    }

    mac_out << mac << std::endl;
    mac_out.close();
}

int main() {
    std::string mac_wlan = read_mac("MACWLAN");
    std::string mac_bt = read_mac("MACBT");

    ALOGI("WLAN MAC %s:xx:xx:xx", mac_wlan.substr(0, 8).c_str());
    ALOGI("BT MAC %s:xx:xx:xx", mac_bt.substr(0, 8).c_str());

    ALOGI("Writing WLAN MAC to %s", WLAN_MAC_FILE);
    write_mac(WLAN_MAC_FILE, mac_wlan.c_str());
    ALOGI("Success!");

    ALOGI("Writing BT MAC to %s", BT_MAC_FILE);
    write_mac(BT_MAC_FILE, mac_bt.c_str());
    ALOGI("Success!");

}

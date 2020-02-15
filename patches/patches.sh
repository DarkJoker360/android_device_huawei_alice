#!/usr/bin/env bash
#
# ROM  patching script for P8 Lite 2015 (alice)
#
# Copyright (C) 2018 DarkJoker360
#
# This program is free software: you can REDistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>
source build/envsetup.sh

echo "Do you want to patch sources for P8 Lite ?"
select yn in "Yes" "No"; do
    case $yn in
        Yes )   echo "Patching bionic/libc/bionic....."
		        cd bionic/libc/bionic && git remote add gps https://github.com/DarkJoker360/android_bionic && git fetch gps && git cherry-pick 05f2b6707a50edbf1cd60dee1b107992b42964b0
                echo "Patching system/bt....."
				cd ../../.. && cd system/bt && git remote add bt https://github.com/DarkJoker360/android_system_bt && git fetch bt && git cherry-pick 46c163e13dbe21476e3fe8e2f94ae10af28f2c5c
                echo "Patching frameworks/native....."
				cd ../.. && cd frameworks/native && git remote add hwc https://github.com/DarkJoker360/android_frameworks_native && git fetch hwc && git cherry-pick a083e29978432dfc04039a224c82925cbcab780f
                echo "Patching frameworks/opt/telephony....."
				cd .. && cd opt/telephony  && git remote add sim https://github.com/DarkJoker360/android_frameworks_opt_telephony && git fetch sim && git cherry-pick 79b503f625a7c0a048f9c891e19cc6be4b2f0e57
				wget https://raw.githubusercontent.com/DarkJoker360/prague_patches/lineage-15.1/frameworks/opt/telephony/0002-Telephony-Don-not-call-onUssdRelease-for-Huawei-RIL.patch
				patch -p1< 0002-Telephony-Don-not-call-onUssdRelease-for-Huawei-RIL.patch
		echo "Patching packages/services/Telephony....."
				cd ../../.. && cd packages/services/Telephony
				wget https://raw.githubusercontent.com/DarkJoker360/android_device_huawei_alice/cm-14.1/patches/packages/services/Telephony/0001-Telephony-Support-muting-by-RIL-command.patch
				patch -p1< 0001-Telephony-Support-muting-by-RIL-command.patch
		echo "Patching packages/apps/Settings....."
				cd ../.. && cd apps/Settings
				wget https://raw.githubusercontent.com/DarkJoker360/android_device_huawei_alice/cm-14.1/patches/packages/apps/Settings/0001-Settings-set-animations-scale-to-0-5x.patch
                		patch -p1< 0001-Settings-set-animations-scale-to-0-5x.patch
		echo "Patching packages/apps/Nfc....."
				cd .. && cd Nfc && git remote add nfc https://github.com/DarkJoker360/android_packages_apps_Nfc && git fetch nfc && git cherry-pick 2834f10f19ad0f232eaa6e2448bf11ead96fa3fb && git cherry-pick 3520f5b2f74a0b4fdafaa95c985cd38ecb6a6ff8 && cd ../../..; break;;
        No ) break;;
    esac
done

echo ""
echo "Now you can build your rom !"

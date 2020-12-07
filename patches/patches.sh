#!/usr/bin/env bash
#
# ROM  patching script for P8 Lite 2015 (alice)
#
# Copyright (C) 2020 DarkJoker360
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

if [ "$(pwd | xargs basename)" = "patches" ]; then
    cd ../../../..
fi

ROOTDIR="$PWD"
THIS_DIR="$PWD/device/huawei/alice/patches"

echo "Patching sources..."
cd frameworks/base
patch -p1 < $THIS_DIR/frameworks/base/0001-Disable-vendor-mismatch-warning.patch
cd ../native
patch -p1 < $THIS_DIR/frameworks/native/0001-surfaceflinger-Fix-deep-sleep-issue.patch
cd ../opt/telephony
patch -p1 < $THIS_DIR/frameworks/opt/telephony/0001-telephony-fix-2g-2g-4g-switch.patch
patch -p1 < $THIS_DIR/frameworks/opt/telephony/0002-Telephony-Don-not-call-onUssdRelease-for-Huawei-RIL.patch
patch -p1 < $THIS_DIR/frameworks/opt/telephony/0003-Make-better-signal-levels-on-Huawei-devices.patch
cd $ROOTDIR
cd packages/apps/Camera2
patch -p1 < $THIS_DIR/packages/apps/Camera2/0001-Fix-flashlight-delay.patch
cd ../../services/Telephony
patch -p1 < $THIS_DIR/packages/services/Telephony/0001-Telephony-Support-muting-by-RIL-command.patch
cd $ROOTDIR

cd vendor/lineage
git fetch https://github.com/DarkJoker360/android_vendor_lineage
git cherry-pick ffaaece5655263f5db69e65e68bed9d3bbca546e
cd ../..

rm -rf system/core/init
git clone https://github.com/DarkJoker360/alice_system_core_init system/core/init

echo "Done..."


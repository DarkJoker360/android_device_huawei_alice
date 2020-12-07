# LineageOS 15.1 for the Huawei P8 Lite (alice)

# Sources needed
### Kernel
This device tree is intended to be used with this kernel repo:

See: https://github.com/DarkJoker360/android_kernel_huawei_alice

branch: lineage-15.1
### Vendor
This device tree is intented to be used with this vendor repo

https://github.com/DarkJoker360/android_vendor_huawei_alice

branch: lineage-15.1

# How To Build

### Step 1: Setting up the Build Environment.

You'll need Linux to be able to build LineageOS 15.1. You have three choices here; you can:

1. Install Linux natively on your computer.
2. Dual boot Linux and Windows.
3. Use virtual machine software ( virtual box, vmware ) to run linux.

NOTE: I recommend you use Ubuntu 14.04 LTS to build. That's what I use.

Now read this: http://source.android.com/source/initializing.html

NOTE: When I say "read", I mean read and comprehend.

### Step 2: Downloading the Source.

NOTE: Some say that it is better to download the ROM source and put in your local manifest later. I don't know if that's best but that's what we are going to do.

BEFORE YOU BEGIN: You are about to start downloading 15 - 20 Gigs of data. That could take a very long time, so plan accordingly. I like to start just before I go to sleep and let it 
go overnight! If you have to work, perhaps start it before work and let it go through out the day.

Execute the following commands in a linux terminal:
```bash
mkdir /home/$USER/los
cd /home/$USER/los
repo init -u git://github.com/LineageOS/android.git -b lineage-15.1
repo sync
```
WARNING: There may be times, towards the end when it seem like, the download is stuck and not making any progress because there are no updates on the screen. BE PATIENT!, open a 
program that will show how much bandwidth you are using to be sure!

### Step 3: Set up local manifest.

The local manifest is different for every device. It contains those repos that are device specific, where as the ROM code you just "repo sync'd" is code that is general to any device.

Execute the following commands in a linux terminal:
```bash
mkdir /home/$USER/los/.repo/local_manifests
gedit /home/$USER/los/.repo/local_manifests/alice.xml
```
Copy the following into alice.xml, save and close.
```bash
<?xml version="1.0" encoding="UTF-8"?>
<manifest>
  <project name="DarkJoker360/android_kernel_huawei_alice" path="kernel/huawei/alice" remote="github" revision="lineage-15.1"/>
  <project name="DarkJoker360/android_device_huawei_alice" path="device/huawei/alice" remote="github" revision="lineage-15.1"/>
  <project name="DarkJoker360/android_vendor_huawei_alice" path="vendor/huawei/alice" remote="github" revision="lineage-15.1"/>
</manifest>
```

Execute the following commands in a linux terminal:
```bash
cd /home/$USER/los
repo sync
```

NOTE: Yes we are syncing again and No, it shouldn't take quite as long. Every time you repo sync just new data is downloaded. So we are downloading the 4 repo's we just put in and any 
updates that may have occured to the repo's we already have.

### Step 4: Building

Now you will want to apply the repo patches. These patches modify code in the ROM to work with this device.
Execute the following commands in a linux terminal:
NOTE: you have to run the chmod command if you have some issues on the script 
```bash
cd /home/$USER/los
./device/huawei/alice/patches/patches.sh
```
NOTE: If you are going to be offline while you are building, you will need download some prebuilts first.
```bash
cd /home/$USER/los
make fetchprebuilts
```
NOTE: Now you have everything that you need to build LineageOS 14 for your Huawei P8 Lite. 
It may take anywhere from 5 hours to 15 hours depending on system specs for a complete build.
Execute the following commands in a linux terminal:
```bash
cd /home/$USER/los
. build/envsetup.sh
lunch lineage_alice-userdebug
mka bacon
```

Huawei P8Lite detailed specifications:
======================================

Basic         |Spec Sheet
-------------:|:--------------------------------------------------------------------------------------------------------------------------
Network	      | GSM / HSPA / LTE
Launch	      |2015, April
Body	      |143 x 70.6 x 7.7 mm (5.63 x 2.78 x 0.30 in); 131 g (4.62 oz); Dual SIM (Nano-SIM/ Micro-SIM, dual stand-by)
Display	      |IPS LCD capacitive touchscreen, 16M colors; 5.0 inches; 720 x 1280 pixels; Corning Gorilla Glass 3
Platform      |Android OS, v5.0.2 (Lollipop), upgradable to v6.0 (Marshmallow)
Chipset	      |HiSilicon Kirin 620
CPU	      |Octa-core 1.2 GHz Cortex-A53
GPU	      |Mali-450MP4
Memory	      |16 GB, 2 GB RAM; microSD, up to 256 GB (uses SIM 2 slot)
Rear Camera   |13 MP, f/2.0, 27mm, autofocus, dual-LED flash, Geo-tagging, touch focus, face/smile detection, panorama, HDR, 1080p@30fps
Front Camera  |5 MP, 720p
Sound	      |- Active noise cancellation with dedicated mic
WLAN	      |Wi-Fi 802.11 a/b/g/n, WiFi Direct, hotspot
Bluetooth     |v4.0, A2DP, EDR, LE
GPS	      |Yes, with A-GPS, GLONASS
NFC	      |Yes
Radio	      |FM radio
USB	      |microUSB v2.0
Sensors	      |Accelerometer, proximity, compass
Battery	      |Non-removable Li-Ion 2200 mAh battery
Colors 	      |Black, White, Gold


![Huawei P8Lite](http://cdn2.gsmarena.com/vv/pics/huawei/huawei-p8-lite.jpg "Huawei P8Lite")

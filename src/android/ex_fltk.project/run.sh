#!/bin/bash -e

echo touch ex_fltk.cpp
touch csrc/ex_fltk.cpp
echo build
ndk-build clean
ndk-build -B
echo install
ant clean debug
adb -d install -r bin/exfltk-debug.apk
echo done
#usb device -d
adb -d shell 'am start -a android.intent.action.MAIN -n org.liballeg.example/.exfltkActivity'
#emulator - e
#adb -e shell 'am start -a android.intent.action.MAIN -n org.liballeg.example/.exfltkActivity'

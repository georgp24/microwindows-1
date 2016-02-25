#!/bin/bash -e

echo touch ex_nanox.c
touch csrc/ex_nanox.c
echo build
ndk-build clean
ndk-build -B
echo install
ant clean debug
adb -d install -r bin/exnanox-debug.apk
echo done
#usb device -d
adb -d shell 'am start -a android.intent.action.MAIN -n org.liballeg.example/.exnanoxActivity'
#emulator - e
#adb -e shell 'am start -a android.intent.action.MAIN -n org.liballeg.example/.exnanoxActivity'

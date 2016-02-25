# Absolute paths to Allegro source and build directories.
CMAKE_SOURCE_DIR := $(HOME)/microwindows-android/src/android/
CMAKE_BINARY_DIR := $(HOME)/microwindows-android/src/android/buildandroid

# Relative path to prebuilt Allegro libraries from LOCAL_PATH.
RELATIVE_LIB_DIR := ../../buildandroid/lib

# Library type suffix on Allegro libraries, e.g. "-debug".
# XXX changing this requires manual editing of the System.loadLibrary calls
LIB_TYPE_SUFFIX := -debug

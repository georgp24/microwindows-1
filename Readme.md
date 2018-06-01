# [NEW: MICROWINDOWS AND FLTK PORTED TO THE ANDROID PLATFORM] (https://github.com/georgp24/microwindows-android-bin)

<img src="https://user-images.githubusercontent.com/10487642/40860132-ca56d428-65d3-11e8-8b3a-5a138e6372b0.png" width="90%"></img> 

Download  this from the Microwindows-Android-bin repo:
<https://github.com/georgp24/microwindows-android-bin>

- - - -

# Microwindows or the Nano-X Window System

Microwindows or Nano-X is a small, Xlib compatible library. It is
Open Source and licenced under the the Mozilla Public License.
The main GUI toolkit that can be used with Microwindows is FLTK,
but XForms is available too. 

## Areas where Microwindows can be used are:

- provide an excellent GUI for small embedded devices with FLTK
- port the FLTK GUI toolkit to new platforms
- linking an application with Microwindows can provide it with a GUI 
  on console based Linux distros
- provide Xlib support for platforms without Xlib

It features two APIs: Nano-X/NX11 which provides an 
X11 compatible API and MWIN which is compatible to the Win32 API.

## Platforms

Microwindows is very portable, is written in C and can be used on a wide range 
of platforms. 

Currently it is available for **Linux, Windows, Mac OS X, Android, DOS, 
uclinux, RTEMS, ELKS, PSP** and more. 

It can be compiled for **x86, x86_64, ARM, PowerPC and MIPS** processors.

## Library design

The Nano-X Window System has a layered design. At the lowest level there are 
drivers for screen output as well as mouse and keyboard input. Touch input 
devices are also supported. Drivers are available for **X11, frame buffer, 
SDL, the Allegro graphics library, VESA or the SVGA library**. Additional 
drivers can be added to port Microwindows to more platforms.

At the mid level, a portable graphics engine is implemented, providing 
support for line draws, area fills, polygons, clipping and color models. 

At the upper level, the Nano-X/NX11 and MWIN API's are implemented 
providing access to the graphics applications programmer. 

The Nano-X Window System can be compiled either as a separate server for 
several clients or linked together to a single, standalone library.

## Web site

The main Nano-X web site is at <http://www.microwindows.org>

## Install

To build Microwindows, see the files /src/INSTALL and /src/CONTENTS 
plus the faq files in the doc directory. For Android there is an
application note in the doc directory.

An HTML based FAQ and Architecture document are available from the web site.

## Links

The chief maintainer of the project is Greg Haerr <greg@censoft.com>

Microwindows and Nano-X are discussed on the NanoGUI mailing list. 
Mailing list archives are available at: 
<http://www.linuxhacker.org/ezmlm-browse/index.cgi?list=nanogui>


#!/bin/sh
clear
case $# in
0) ls -C ~/microwindows/src/demos/nanox/*.c
   echo -n "Please enter program name including suffix: "
   read progname
   cp ~/microwindows/src/demos/nanox/$progname ex_nanox.c ;;
1) cp ~/microwindows/src/demos/nanox/$1 ex_nanox.c ;;
esac

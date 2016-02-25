#!/bin/sh
clear
case $# in
0) ls -C ~/fltk-1.3.3/test/*.cxx
   echo -n "Please enter program name including suffix: "
   read progname
   cp ~/fltk-1.3.3/test/$progname ex_fltk.cpp ;;
1) cp ~/fltk-1.3.3/test/$1 ex_fltk.cpp ;;
esac

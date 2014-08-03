# -*- makefile -*-
# Select compiler by changing CC.

ifeq (default,$(origin CC))
    CC=C:\mingw64-i686-20110207\bin\gcc.exe
    CXX=C:\mingw64-i686-20110207\bin\g++.exe
endif

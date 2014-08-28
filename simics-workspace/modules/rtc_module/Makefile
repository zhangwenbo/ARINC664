# -*- makefile -*-
#
# Sample makefile for the DML device: "empty-dml-device"
# See Simics Model Builder User Guide for more details on what to put here.
#

MODULE_CLASSES = rtc_module
SRC_FILES = socket.c rdc_load_conf.c op_429_card.c
DML_FILES = rtc_module.dml
DMLC_FLAGS = -m -I$(SIMICS_WORKSPACE)/include

MODULE_CFLAGS = -I$(SIMICS_WORKSPACE)/modules/rtc_module/include
MODULE_LDFLAGS = -lws2_32 -L$(SIMICS_WORKSPACE)/modules/rtc_module/lib/win -la429

SIMICS_API := 4.6
THREAD_SAFE := yes

ifeq ($(MODULE_MAKEFILE),)
$(error Make sure you compile your module from the workspace directory)
else
include $(MODULE_MAKEFILE)
endif

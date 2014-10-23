# -*- makefile -*-
#
# Sample makefile for the DML device: "empty-dml-device"
# See Simics Model Builder User Guide for more details on what to put here.
#

MODULE_CLASSES = sample_frame_module
SRC_FILES = save_frame_into_disk.c
DML_FILES = sample-frame-module.dml 
DMLC_FLAGS = -m -I$(SIMICS_WORKSPACE)/include

SIMICS_API := 4.6
THREAD_SAFE := yes

ifeq ($(MODULE_MAKEFILE),)
$(error Make sure you compile your module from the workspace directory)
else
include $(MODULE_MAKEFILE)
endif

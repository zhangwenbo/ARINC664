# -*- makefile -*-
#
# Sample makefile for the DML device: "empty-dml-device"
# See Simics Model Builder User Guide for more details on what to put here.
#

MODULE_CLASSES = afdxES
SRC_FILES = tomiddleware.c
DML_FILES = afdxES.dml
DMLC_FLAGS = -m -I$(SIMICS_WORKSPACE)/include

MODULE_CFLAGS = -I$(SIMICS_WORKSPACE)/modules/afdxES/inc/  
MODULE_LDFLAGS = $(SIMICS_WORKSPACE)\modules\afdxES\lib\AFDX_Card.lib -lws2_32
 
SIMICS_API := 4.6
THREAD_SAFE := yes

ifeq ($(MODULE_MAKEFILE),)
$(error Make sure you compile your module from the workspace directory)
else
include $(MODULE_MAKEFILE)
endif

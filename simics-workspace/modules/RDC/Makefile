# -*- makefile -*-
#
# Sample makefile for the DML device: "empty-dml-device"
# See Simics Model Builder User Guide for more details on what to put here.
#

MODULE_CLASSES = RDC
SRC_FILES = rdc_load_conf.c op_429_card.c untils.c rdc_runtime_info.c
DML_FILES = RDC.dml
DMLC_FLAGS = -m -I$(SIMICS_WORKSPACE)/include 

MODULE_CFLAGS = -I$(SIMICS_WORKSPACE)/modules/RDC/include/  

MODULE_LDFLAGS = $(SIMICS_WORKSPACE)\modules\RDC\lib\win\a429.lib -lws2_32
SIMICS_API := 4.6
THREAD_SAFE := yes

ifeq ($(MODULE_MAKEFILE),)
$(error Make sure you compile your module from the workspace directory)
else
include $(MODULE_MAKEFILE)
endif

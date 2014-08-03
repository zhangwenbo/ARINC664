# -*- makefile -*-
# Do not edit. This file will be overwritten by the workspace setup script.

.SUFFIXES:

# Check for MinGW Make 3.81 or newer before trying to invoke cmd.exe
make_banner:=$(shell $(MAKE) --version)
make_version:=$(filter 3.%,$(make_banner))
err_message=$(warning You need MinGW make 3.81 or newer in order to build modules.)    \
	    $(warning Try compiling with bin\make.bat or)		      \
            $(warning refer to the "Simics Model Builder User Guide" document) \
            $(warning for more information.)				      \
            $(error Unsupported make version)

# Check for old unsupported version that may still be in use
ifneq ($(or $(filter 3.79,$(make_version)),$(filter 3.80,$(make_version))),)
    $(warning Your version of make is $(make_version).)
    $(err_message)
endif

# i686-pc-cygwin will invoke cmd.exe with wrong arguments.
# i686-pc-mingw is verified to work.
ifneq ($(findstring mingw,$(make_banner)),mingw)
    $(warning make binary does not appear to be a MingW make.)
    $(err_message)
endif

export SHELL=cmd.exe

ifneq ($(VERBOSE),yes)
    MAKEFLAGS += -s
endif

# change all '/' to '\' to allow the path to be used in a pure Windows way
W_PATH = $(subst /,\,$(1))
# change all '\' to '/' to allow the path to be used with make file matching
S_PATH = $(subst \,/,$(1))

export W_PATH
export S_PATH

include config.mk

# allow user to override HOST_TYPE
ifeq (,$(HOST_TYPE))
    HOST_TYPE:=$(shell $(PYTHON) $(W_SIMICS_BASE)\scripts\host_type.py)
endif

ifeq (,$(HOST_TYPE))
    $(error "Could not determine host-type (HOST_TYPE variable not set)")
endif

ifeq ($(TARGET_DIR),)
    TARGET_DIR:=$(SIMICS_WORKSPACE)/$(HOST_TYPE)/lib
endif

W_TARGET_DIR:=$(call W_PATH,$(TARGET_DIR))

export TARGET_DIR
export W_TARGET_DIR

.PHONY: default
default: all

ifeq ($(ENVCHECK),disable)
    ENVCHECK_FLAG=
else
    include $(SIMICS_MODEL_BUILDER)/config/workspace/envcheck.mk.win32
    ENVCHECK_FLAG:=$(HOST_TYPE)/.environment-check/all
endif


MODULE_MAKEFILE := $(SIMICS_MODEL_BUILDER)/config/workspace/module.mk.win32

$(W_TARGET_DIR):
	if not exist $(W_TARGET_DIR) mkdir $(W_TARGET_DIR)
MODULE_OBJDIR=$(W_SIMICS_WORKSPACE)\$(HOST_TYPE)\obj\modules\$@

ifeq (,$(WORKSPACE_SRC_DIR))
WORKSPACE_SRC_DIR=modules
endif

ifeq ($(DEEP_SOURCE_SEARCH),yes)

# build targets.cache as a side effect of a $(shell) call. This is ugly, but
# less ugly than the alternatives
_:=$(shell if not exist $(W_TARGET_DIR) mkdir $(W_TARGET_DIR))
_:=$(shell $(PYTHON)							 \
	   $(W_SIMICS_MODEL_BUILDER)\scripts\build\build-target-cache.py \
	      --source-dir $(WORKSPACE_SRC_DIR) -w > $(W_TARGET_DIR)\targets.cache)

-include $(TARGET_DIR)/targets.cache

else

MODULES:=$(patsubst $(WORKSPACE_SRC_DIR)/%/Makefile,%,$(wildcard $(WORKSPACE_SRC_DIR)/*/Makefile))

.PHONY: all test help $(MODULES)
all: $(MODULES)

$(MODULES): $(ENVCHECK_FLAG) $(W_TARGET_DIR)
	if not exist $(MODULE_OBJDIR) mkdir $(MODULE_OBJDIR)
	@echo === Building module "$@" ===
	$(MAKE) -r -R							\
	    --directory=$(MODULE_OBJDIR)				\
	    -f $(W_SIMICS_WORKSPACE)\$(WORKSPACE_SRC_DIR)\$@\Makefile		\
	    MOD_MAKEFILE=$(SIMICS_WORKSPACE)/$(WORKSPACE_SRC_DIR)/$@/Makefile	\
	    HOST_TYPE=$(HOST_TYPE)					\
	    SRC_BASE=$(SIMICS_WORKSPACE)/$(WORKSPACE_SRC_DIR)			\
	    MODULE_MAKEFILE="$(MODULE_MAKEFILE)"			\
	    TARGET=$@

help:
	@echo Available modules: $(MODULES)
	@echo Show build commands: make VERBOSE=yes

test: all
	$(W_SIMICS_WORKSPACE)\bin\test-runner.bat --basedir $(WORKSPACE_SRC_DIR)

test-%: %
	$(W_SIMICS_WORKSPACE)\bin\test-runner.bat --basedir $(WORKSPACE_SRC_DIR) $*

endif

get_source_dir:
	@echo $(WORKSPACE_SRC_DIR)

MODULE_CLEAN   := $(addprefix clean-,$(MODULES))
MODULE_CLOBBER := $(addprefix clobber-,$(MODULES))

RMDIR=rmdir /s /q
RM_OR_MOVE=$(PYTHON) $(W_SIMICS_MODEL_BUILDER)\scripts\build\rm_or_move.py
CLEAN_TARGET=$(patsubst clean-%,%,$@)
CLOBBER_TARGET=$(patsubst clobber-%,%,$@)
MODULE_PYNAME= $(subst -,_,$(CLOBBER_TARGET))

.PHONY: $(MODULE_CLEAN) $(MODULE_CLOBBER) clean clobber

$(MODULE_CLEAN):
	@echo Clean of module: $(CLEAN_TARGET)
	if exist $(HOST_TYPE)\obj\modules\$(CLEAN_TARGET) $(RMDIR) $(HOST_TYPE)\obj\modules\$(CLEAN_TARGET)

$(MODULE_CLOBBER):
	@echo Removing module: $(CLOBBER_TARGET)
	if exist $(HOST_TYPE)\obj\modules\$(CLOBBER_TARGET) $(RMDIR) $(HOST_TYPE)\obj\modules\$(CLOBBER_TARGET)
	$(RM_OR_MOVE) \
	  $(HOST_TYPE)\lib\$(CLOBBER_TARGET).$(SO_SFX) \
	  $(HOST_TYPE)\lib\python\mod_$(MODULE_PYNAME)_commands.pyc \
	  $(HOST_TYPE)\lib\python\mod_$(MODULE_PYNAME)_gcommands.pyc \
	  $(HOST_TYPE)\lib\$(MODULE_PYNAME).pyc \
	  $(HOST_TYPE)\lib\$(MODULE_PYNAME).pymod

clean:
	@echo Clean of all modules
	if exist $(HOST_TYPE)\obj $(RMDIR) $(HOST_TYPE)\obj
	if exist $(HOST_TYPE)\.environment-check $(RMDIR) $(HOST_TYPE)\.environment-check

clobber: clean
	@echo Removing all modules
	if exist $(HOST_TYPE)\lib $(RMDIR) $(HOST_TYPE)\lib

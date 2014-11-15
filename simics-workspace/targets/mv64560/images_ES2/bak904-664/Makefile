all:net  checkSize

WIND_BASE := $(subst \,/,$(WIND_BASE))
include $(WIND_BASE)/target/config/make/Makefile.vars


BUILD_SPEC :=debug
TOOL_CHAIN := gnu

BUILD_DIR :=$(CPU)$(TOOL_CHAIN).$(BUILD_SPEC)

COREOS_DIR :=../mos
POS_DIR :=../pos
APP1_DIR :=../app1
APP2_DIR :=../app2
INT_DIR :=../int

XML_FILE = ../../src/xml/app-module.xml
SM_FILES  = $(shell $(XMLGEN_FILES) $(XML_FILE))
SYM_FILES = $(shell $(XMLGEN_FILES) --sym $(XML_FILE))

BIN_FILES = $(shell $(XMLGEN_FILES) --bin $(XML_FILE))

include $(WIND_BASE)/target/config/make/Makefile.rules

payloadObjs_rom.o: $(COREOS_DIR)/$(BUILD_DIR)/payloadObjs_rom.o 
	cp $< $@
coreOS.sm:$(COREOS_DIR)/$(BUILD_DIR)/coreOS.sm
	cp $< $@
pos.sm: $(POS_DIR)/pos.sm
	cp  $< $@
app1.sm:$(APP1_DIR)/app1.sm
	cp  $< $@
app2.sm:$(APP2_DIR)/app2.sm
	cp  $< $@


# Downloadable symbol tables

net: $(SYM_FILES)	

BINFLAGS_EXTRA = $(shell $(XMLGEN_BINFLAGS) -j $* configRecord.xml)
$(BIN_FILES): configRecord.xml

checkSize: $(SM_FILES)	
	xmlgen --bbCheck $(addprefix -j ,$(basename $^)) configRecord.xml
		
.PHONY clean:
	rm -rf *.sm	
	rm -rf *.sym	
	rm -rf configRecord.*


	
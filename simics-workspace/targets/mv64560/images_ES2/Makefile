#######################################
#####Integration Makefile Template#####
#######################################
WIND_BASE := $(subst \,/,$(WIND_BASE))
DEMO_TOOLCHAIN = PPC604gnu.debug

all: net checkSize

include $(WIND_BASE)/target/config/make/Makefile.vars

XML_FILE  = ../demo.xml
SM_FILES  = $(shell $(XMLGEN_FILES) $(XML_FILE))
SYM_FILES = $(shell $(XMLGEN_FILES) --sym $(XML_FILE))
BIN_FILES = $(shell $(XMLGEN_FILES) --bin $(XML_FILE))
MOS_SYM_FILE := $(shell $(XMLGEN_FILES) --sym --only-coreos $(XML_FILE))

MOS_DIR	 = ../mos
POS_DIR  = ../pos
PRJ_BASE = ../

include $(WIND_BASE)/target/config/make/Makefile.rules

coreOS.sm: $(MOS_DIR)/$(DEMO_TOOLCHAIN)/coreOS.sm ; cp $< $@
payloadObjs_ram.o: $(MOS_DIR)/$(DEMO_TOOLCHAIN)_ramPayload/payloadObjs_ram.o ; cp $< $@
payloadObjs_rom.o: $(MOS_DIR)/$(DEMO_TOOLCHAIN)_romPayload/payloadObjs_rom.o ; cp $< $@
pos.sm:    $(POS_DIR)/pos.sm                       ; cp $< $@
AppTest1_part.sm: $(PRJ_BASE)/AppTest1/AppTest1_part.sm ; cp $< $@
AppTest2_part.sm: $(PRJ_BASE)/AppTest2/AppTest2_part.sm ; cp $< $@
AppTest3_part.sm: $(PRJ_BASE)/AppTest3/AppTest3_part.sm ; cp $< $@
 
# Downloadable symbol tables
net: $(SYM_FILES)

BINFLAGS_EXTRA = $(shell $(XMLGEN_BINFLAGS) -j $* configRecord.xml)

$(BIN_FILES): configRecord.xml

checkSize: $(SM_FILES)
	xmlgen --bbCheck $(addprefix -j ,$(basename $^)) configRecord.xml

sms_ramPayload.sym: $(MOS_SYM_FILE)
	cp $< $@

clean:
	rm -f *.sm
	rm -f *.sym
	rm -f *.bin
	rm -f *.xml
	rm -f *.o
	rm -f boot.txt
	rm -f configRecord.reloc
	rm -f sms_ramPayload*
	rm -f sms_romPayload*

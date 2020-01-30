# find the os
UNAME_S     := $(shell uname -s)

#Compiler and Linker depending on OS
CC          := cc 

#The Target Binary Program
TARGET      := ort

#Common variables for Direcories and Files.
SRCDIR      := src
INCDIR      := inc
BUILDDIR    := obj
TARGETDIR   := bin
RESDIR      := res
SRCEXT      := c
OBJEXT      := o

#Build Link Flags, and Libraries
CFLAGS      :=
LIB         := -lm -lcurl -lmosquitto -pthread
INC         := -I$(INCDIR) -I . -I duktape
INCDEP      := -I$(INCDIR)

#---------------------------------------------------------
# Build Commands 
#---------------------------------------------------------
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))
RESOURCES   := $(shell find $(RESDIR) -type f)

# if running on Mac OS enable debugging.
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -D MAC_DEBUG=1
endif

#Defauilt Make
all: resources $(TARGET)

#Rebuild
rebuild: clean all 

#Copy Resources from Resources Directory to Target Directory
resources: directories
ifneq ($(RESOURCES),)
	@cp -r $(RESDIR)/* $(TARGETDIR)/
endif

#Make the Directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

#Clean all Objects and Binaries
clean:
	@$(RM) -rf $(BUILDDIR)
	@$(RM) -rf $(TARGETDIR)

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

#Link
$(TARGET): $(OBJECTS)
	@echo " Linking... $^"
	@mkdir -p $(TARGETDIR)
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@echo " Compiling....  $@"
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

#Non-File Targets
.PHONY: all remake clean cleaner resources



#test: CFLAGS += -D MAC_DEBUG=1 -g -O0 -ggdb3
#
#test: all
#	service mosquitto start
#	cp bin/ort .
#	./ort ../test/buffer.js

info:
	@echo "INFO!"
	@echo "SOURCES=$(SOURCES)"
	@echo "OBJECTS=$(OBJECTS)"
	@echo "CC=$(CC)"
	@echo "CFLAGS=$(CFLAGS)"
	@echo "LDFLAGS=$(LDFLAGS)"
	@echo "LIB=$(LIB)"
	@echo "RESOURCES=$(RESOURCES)"

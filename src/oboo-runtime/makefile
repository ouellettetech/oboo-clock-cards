# find the os
UNAME_S     := $(shell uname -s)

#Compiler and Linker depending on OS
CC          := cc 

#The Target Binary Program
COMPONENT_NAME      := ort

# Test Input's
PROJECT_HOME_DIR = .
ifeq "$(CPPUTEST_HOME)" ""
    CPPUTEST_HOME = ~/tools/cpputest
endif

#Set this to @ to keep the makefile quiet
SILENCE = @

#Common variables for Direcories and Files.
SRC_DIRS    := src
INCDIR      := inc
BUILDDIR    := obj
TARGETDIR   := bin
RESDIR      := res
SRCEXT      := c
TESTEXT     := cpp
OBJEXT      := o

# --- TEST_SRC_FILES and TEST_SRC_DIRS ---
# Test files are always included in the build.
# Production code is pulled into the build unless
# it is overriden by code of the same name in the
# test code.
#
# TEST_SRC_FILES specifies individual test files to build.  
# TEST_SRC_DIRS, builds everything in the directory
TEST_SRC_FILES +=
TEST_SRC_DIRS  += test-src
TEST_SRC_DIRS  += test-src/mocks

# --- MOCKS_SRC_DIRS ---
# MOCKS_SRC_DIRS specifies a directories where you can put your
# mocks, stubs and fakes.  You can also just put them
# in TEST_SRC_DIRS
MOCKS_SRC_DIRS += test-src/mocks

# Turn on CppUMock
CPPUTEST_USE_EXTENSIONS = Y



# INCLUDE_DIRS are searched in order after the included file's
# containing directory
INCLUDE_DIRS += $(CPPUTEST_HOME)/include
INCLUDE_DIRS += $(CPPUTEST_HOME)/include/Platforms/Gcc
INCLUDE_DIRS += src
#INCLUDE_DIRS += test-src/exploding-fakes

#Build Link Flags, and Libraries
CFLAGS      :=
LIB         := -lm -lcurl -lmosquitto -pthread
INC         := -I$(INCDIR) -I . -I duktape
INCDEP      := -I$(INCDIR)


# --- CPPUTEST_OBJS_DIR ---
# CPPUTEST_OBJS_DIR lets you control where the
# build artifact (.o and .d) files are stored.
#
# If you have to use "../" to get to your source path
# the makefile will put the .o and .d files in surprising
# places.
#
# To make up for each level of "../"in the source path,
# add place holder subdirectories to CPPUTEST_OBJS_DIR
# each.  
# e.g. if you have "../../src", set to "test-objs/1/2"
#
# This is kind of a kludge, but it causes the
# .o and .d files to be put under objs.
CPPUTEST_OBJS_DIR = test-obj

CPPUTEST_LIB_DIR = test-lib

# You may have to tweak these compiler flags
#    CPPUTEST_WARNINGFLAGS - apply to C and C++
#    CPPUTEST_CFLAGS - apply to C files only
#    CPPUTEST_CXXFLAGS - apply to C++ files on;y
#    CPPUTEST_CPPFLAGS - apply to C and C++ Pre-Processor
#
# If you get an error like this
#     TestPlugin.h:93:59: error: 'override' keyword is incompatible
#        with C++98 [-Werror,-Wc++98-compat] ...
# The compiler is basically telling you how to fix the
# build problem.  You would add this flag setting
#     CPPUTEST_CXXFLAGS += -Wno-c++14-compat




# Some flags to quiet clang
ifeq ($(shell $(CC) -v 2>&1 | grep -c "clang"), 1)
CPPUTEST_WARNINGFLAGS += -Wno-unknown-warning-option
CPPUTEST_WARNINGFLAGS += -Wno-covered-switch-default
CPPUTEST_WARNINGFLAGS += -Wno-reserved-id-macro
CPPUTEST_WARNINGFLAGS += -Wno-keyword-macro
CPPUTEST_WARNINGFLAGS += -Wno-documentation
CPPUTEST_WARNINGFLAGS += -Wno-missing-noreturn
endif

CPPUTEST_WARNINGFLAGS += -Wall
CPPUTEST_WARNINGFLAGS += -Werror
CPPUTEST_WARNINGFLAGS += -Wfatal-errors
CPPUTEST_WARNINGFLAGS += -Wswitch-default
CPPUTEST_WARNINGFLAGS += -Wno-format-nonliteral
CPPUTEST_WARNINGFLAGS += -Wno-sign-conversion
CPPUTEST_WARNINGFLAGS += -Wno-pedantic
CPPUTEST_WARNINGFLAGS += -Wno-shadow
CPPUTEST_WARNINGFLAGS += -Wno-missing-field-initializers
CPPUTEST_WARNINGFLAGS += -Wno-unused-parameter
CPPUTEST_WARNINGFLAGS += -Wno-inconsistent-missing-destructor-override
CPPUTEST_WARNINGFLAGS += -Wno-disabled-macro-expansion
CPPUTEST_WARNINGFLAGS += -Wno-used-but-marked-unused
CPPUTEST_WARNINGFLAGS += -Wno-unused-macros

CPPUTEST_WARNINGFLAGS += -Wno-float-equal
CPPUTEST_WARNINGFLAGS += -Wno-comma
CPPUTEST_WARNINGFLAGS += -Wno-double-promotion
CPPUTEST_WARNINGFLAGS += -Wno-bad-function-cast
CPPUTEST_WARNINGFLAGS += -Wno-conversion
CPPUTEST_WARNINGFLAGS += -Wno-conditional-uninitialized
CPPUTEST_WARNINGFLAGS += -Wno-tentative-definition-incomplete-type
CPPUTEST_CFLAGS += -pedantic
CPPUTEST_CFLAGS += -Wno-missing-prototypes
CPPUTEST_CFLAGS += -Wno-strict-prototypes
CPPUTEST_CXXFLAGS += -Wno-c++14-compat
CPPUTEST_CXXFLAGS += --std=c++11
CPPUTEST_CXXFLAGS += -Wno-c++98-compat-pedantic
CPPUTEST_CXXFLAGS += -Wno-c++98-compat

CPPUTEST_LDFLAGS += $(LIB)
#---------------------------------------------------------
# Build Commands 
#---------------------------------------------------------
SRC_FILES      := $(shell find $(SRC_DIRS) -type f -name *.$(SRCEXT))
#TEST_SRC_FILES += $(shell find $(TEST_SRC_DIRS) -type f -name *.$(TESTEXT))
OBJECTS        := $(patsubst $(SRC_DIRS)/%,$(BUILDDIR)/%,$(SRC_FILES:.$(SRCEXT)=.$(OBJEXT)))
RESOURCES      := $(shell find $(RESDIR) -type f)

# if running on Mac OS enable debugging.
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -D MAC_DEBUG=1
endif

#Defauilt Make
all: resources $(COMPONENT_NAME)

#Rebuild
rebuild: clean cleaner all 

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
cleaner:
	@$(RM) -rf $(BUILDDIR)
	@$(RM) -rf $(TARGETDIR)

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

#Link
$(COMPONENT_NAME): $(OBJECTS)
	@echo " Linking... $^"
	@mkdir -p $(TARGETDIR)
	$(CC) -o $(TARGETDIR)/$(COMPONENT_NAME) $^ $(LIB)

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRC_DIRS)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@echo " Compiling....  $@"
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRC_DIRS)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
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
	@echo "SOURCES=$(SRC_FILES)"
	@echo "OBJECTS=$(OBJECTS)"
	@echo "CC=$(CC)"
	@echo "CFLAGS=$(CFLAGS)"
	@echo "LDFLAGS=$(LDFLAGS)"
	@echo "LIB=$(LIB)"
	@echo "RESOURCES=$(RESOURCES)"


# Look at $(CPPUTEST_HOME)/build/MakefileWorker.mk for more controls

include $(CPPUTEST_HOME)/build/MakefileWorker.mk
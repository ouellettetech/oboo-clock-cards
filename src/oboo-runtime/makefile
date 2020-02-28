# find the os
UNAME_S     := $(shell uname -s)

#Compiler and Linker depending on OS
CC          := cc 

#The Target Binary Program
COMPONENT_NAME      := ort

# Test Input's
PROJECT_HOME_DIR = .

#Set this to @ to keep the makefile quiet
SILENCE = @

#Common variables for Direcories and Files.
SRC_DIRS          := src
INCDIR            := inc
BUILDDIR          := obj
TARGETDIR         := bin
RESDIR            := res
SRCEXT            := c
TESTEXT           := c
OBJEXT            := o
UNITY_ROOT        =../Unity

RESULT_EXT        := txt
PATHU             :=../Unity
PATHS             := src
PATHT             := test-src
PATHB             := build
PATHD             := build/depends
PATHO             := build/objs
PATHR             := build/results
PATH_TEST_RUNNERS := build/test_runners

SRCT = $(wildcard $(PATHT)/*.c)

COMPILE=$(CC) -c
LINK=$(CC)
DEPEND=$(CC) -MM -MG -MF
TEST_CFLAGS :=-I. -I$(PATHU)/src -I$(PATHS) -DTEST

RESULTS = $(patsubst $(PATHT)/Test%.c,$(PATHR)/Test%.txt,$(SRCT) )

PASSED = `grep -s PASS $(PATHR)/*.txt`
FAIL = `grep -s FAIL $(PATHR)/*.txt`
IGNORE = `grep -s IGNORE $(PATHR)/*.txt`

# --- TEST_SRC_FILES and TEST_SRC_DIRS ---
# Test files are always included in the build.
# Production code is pulled into the build unless
# it is overriden by code of the same name in the
# test code.
#
# TEST_SRC_FILES specifies individual test files to build.  
# TEST_SRC_DIRS, builds everything in the directory
#TEST_SRC_FILES += $(UNITY_ROOT)/src/unity.c
#TEST_INC_DIRS  +=-Isrc -I$(UNITY_ROOT)/src
#TEST_SRC_DIRS  += test-src

# --- MOCKS_SRC_DIRS ---
# MOCKS_SRC_DIRS specifies a directories where you can put your
# mocks, stubs and fakes.  You can also just put them
# in TEST_SRC_DIRS
#MOCKS_SRC_DIRS += test-src/mocks

#Build Link Flags, and Libraries
CFLAGS      :=
LIB         := -lm -lcurl -lmosquitto -pthread
INC         := -I$(INCDIR) -I . -I duktape
INCDEP      := -I$(INCDIR)
TEST_INC    := -Isrc -I$(UNITY_ROOT)/src $(INC)

#---------------------------------------------------------
# Build Commands 
#---------------------------------------------------------
SRC_FILES      := $(shell find $(SRC_DIRS) -type f -name *.$(SRCEXT))
#TEST_SRC_FILES += $(shell find $(TEST_SRC_DIRS) -type f -name *.$(TESTEXT))
OBJECTS        := $(patsubst $(SRC_DIRS)/%,$(BUILDDIR)/%,$(SRC_FILES:.$(SRCEXT)=.$(OBJEXT)))
#TEST_OBJECTS   := $(patsubst $(TEST_SRC_DIRS)/%,$(BUILDDIR)/%,$(TEST_SRC_FILES:.$(TESTEXT)=.$(OBJEXT)))
RESOURCES      := $(shell find $(RESDIR) -type f)

# if running on Mac OS enable debugging.
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -D MAC_DEBUG=1
endif

#Defauilt Make
all: info resources test $(COMPONENT_NAME)

test: directories $(RESULTS)
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo "$(IGNORE)"
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo "$(FAIL)"
	@echo "-----------------------\nPASSED:\n-----------------------"
	@echo "$(PASSED)" 
	@echo "\nDONE"
	! grep -s FAIL $(PATHR)/*.txt

$(PATHO)/%.o:: $(PATHT)/%.c
	$(COMPILE) $(TEST_CFLAGS) $< -o $@

$(PATHO)/%.o:: $(PATH_TEST_RUNNERS)/%.c
	$(COMPILE) $(TEST_CFLAGS) $< -o $@

$(PATHO)/%.o:: $(PATHS)/%.c
	$(COMPILE) $(TEST_CFLAGS) $< -o $@

$(PATHO)/%.o:: $(PATHU)/src/%.c $(PATHU)/src/%.h
	$(COMPILE) $(TEST_CFLAGS) $< -o $@

$(PATHD)/%.d:: $(PATHT)/%.c
	$(DEPEND) $@ $<

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
	@mkdir -p $(PATH_TEST_RUNNERS)
	@mkdir -p $(PATHB)
	@mkdir -p $(PATHD)
	@mkdir -p $(PATHO)
	@mkdir -p $(PATHR)

#Clean all Objects and Binaries
clean:
	@$(RM) -rf $(BUILDDIR)
	@$(RM) -rf $(TARGETDIR)
	@$(RM) -rf $(PATHO)/*.o
	@$(RM) -rf $(PATHB)/*
	@$(RM) -rf $(PATHR)/*.txt

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

#Link
$(COMPONENT_NAME): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo "Build with $(CC)"
	@echo " Linking... $^"
	$(CC) -o $(TARGETDIR)/$(COMPONENT_NAME) $^ $(LIB)

$(PATHR)/Test%.txt: $(PATHB)/test%
	echo "PASS 5" > $@ 2>&1
#	#-./$< > $@ 2>&1


# Building Test Runner
$(PATH_TEST_RUNNERS)/TestProductionCode_Runner.c: $(PATHT)/TestProductionCode.c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb $(PATHT)/TestProductionCode.c $(PATH_TEST_RUNNERS)/TestProductionCode_Runner.c
$(PATH_TEST_RUNNERS)/TestProductionCode2_Runner.c: $(PATHT)/TestProductionCode2.c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb $(PATHT)/TestProductionCode2.c $(PATH_TEST_RUNNERS)/TestProductionCode2_Runner.c

# Building Test Runner
#$(PATH_TEST_RUNNERS)/TestProductionCode_Runner.c: $(PATHT)/TestProductionCode.c
#	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb $(PATHT)/TestProductionCode.c $(PATH_TEST_RUNNERS)/TestProductionCode_Runner.c
#
#ruby ../Unity/auto/generate_test_runner.rb test-src/TestProductionCode.c  build/test_runners/TestProductionCode_Runner.c
# Building Test Runner
#$(PATH_TEST_RUNNERS)/Test%_Runner.c: $(PATHT)/Test%.c
#	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb $(PATHT)/Test%.c  $(PATH_TEST_RUNNERS)/Test%_Runner.c


#Link Test Code.
$(PATHB)/test%: $(PATHO)/Test%.$(OBJEXT) $(PATHO)/Test%_Runner.$(OBJEXT) $(PATHO)/unity.$(OBJEXT) $(BUILDDIR)/%.$(OBJEXT) #$(PATHD)Test%.d
	@echo "Linking Test.... $(PATHB)/$@"
	$(LINK) -o $@ $^

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
.PHONY: all remake clean resources

info:
	@echo "INFO!"
	@echo "SOURCES=$(SRC_FILES)"
	@echo "OBJECTS=$(OBJECTS)"
	@echo "CC=$(CC)"
	@echo "CFLAGS=$(CFLAGS)"
	@echo "LDFLAGS=$(LDFLAGS)"
	@echo "LIB=$(LIB)"
	@echo "RESOURCES=$(RESOURCES)"
	@echo "BUILD_PATHS=$(BUILD_PATHS)"
	@echo "RESULTS=$(RESULTS)"
	@echo "PATHR=$(PATHR)"
	@echo "Result command: $(PATHR)/%.$(RESULT_EXT): $(PATHB)/%"

.PRECIOUS: $(PATHB)/test%
.PRECIOUS: $(PATHD)/%.d
.PRECIOUS: $(PATHO)/%.o
.PRECIOUS: $(PATHR)/%.txt
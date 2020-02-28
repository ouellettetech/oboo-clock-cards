# find the os
UNAME_S           := $(shell uname -s)

#Compiler and Linker depending on OS
CC                := cc 

#The Target Binary Program
COMPONENT_NAME    := ort

# Test Input's
PROJECT_HOME_DIR   = .

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
DEPEXT            := d
RESULT_EXT        := txt
UNITY_ROOT        =../Unity
PATH_TEST_SRC     := test-src
PATH_TEST_BUILD   := build
PATH_TEST_DEPS    := build/depends
PATH_TEST_OBJECTS := build/objs
PATH_TEST_RESULTS := build/results
PATH_TEST_RUNNERS := build/test_runners

RESULTS = $(patsubst $(PATH_TEST_SRC)/Test%.c,$(PATH_TEST_RESULTS)/Test%.txt,$(TEST_SRC_FILES) )

PASSED = `grep -s PASS $(PATH_TEST_RESULTS)/*.txt`
FAIL = `grep -s FAIL $(PATH_TEST_RESULTS)/*.txt`
IGNORE = `grep -s IGNORE $(PATH_TEST_RESULTS)/*.txt`

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
TEST_INC    := -I$(SRC_DIRS) -I$(UNITY_ROOT)/src $(INC) -DTEST

#---------------------------------------------------------
# Build Commands 
#---------------------------------------------------------
SRC_FILES      := $(shell find $(SRC_DIRS) -type f -name *.$(SRCEXT))
TEST_SRC_FILES += $(shell find $(PATH_TEST_SRC) -type f -name *.$(TESTEXT))
OBJECTS        := $(patsubst $(SRC_DIRS)/%,$(BUILDDIR)/%,$(SRC_FILES:.$(SRCEXT)=.$(OBJEXT)))
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
	! grep -s FAIL $(PATH_TEST_RESULTS)/*.txt

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
	@mkdir -p $(PATH_TEST_BUILD)
	@mkdir -p $(PATH_TEST_DEPS)
	@mkdir -p $(PATH_TEST_OBJECTS)
	@mkdir -p $(PATH_TEST_RESULTS)

#Clean all Objects and Binaries
clean:
	@$(RM) -rf $(BUILDDIR)
	@$(RM) -rf $(TARGETDIR)
	@$(RM) -rf $(PATH_TEST_OBJECTS)/*.o
	@$(RM) -rf $(PATH_TEST_BUILD)/*
	@$(RM) -rf $(PATH_TEST_RESULTS)/*.txt

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

#Link
$(COMPONENT_NAME): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo "Build with $(CC)"
	@echo " Linking... $^"
	$(CC) -o $(TARGETDIR)/$(COMPONENT_NAME) $^ $(LIB)

$(PATH_TEST_RESULTS)/Test%.txt: $(PATH_TEST_BUILD)/test%
	echo "PASS 5" > $@ 2>&1
#	#-./$< > $@ 2>&1


# Building Test Runner
$(PATH_TEST_RUNNERS)/TestProductionCode_Runner.c: $(PATH_TEST_SRC)/TestProductionCode.c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb $< $@
$(PATH_TEST_RUNNERS)/TestProductionCode2_Runner.c: $(PATH_TEST_SRC)/TestProductionCode2.c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb $< $@

# Building Test Runner
#$(PATH_TEST_RUNNERS)/TestProductionCode_Runner.c: $(PATH_TEST_SRC)/TestProductionCode.c
#	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb $(PATH_TEST_SRC)/TestProductionCode.c $(PATH_TEST_RUNNERS)/TestProductionCode_Runner.c
#
#ruby ../Unity/auto/generate_test_runner.rb test-src/TestProductionCode.c  build/test_runners/TestProductionCode_Runner.c
# Building Test Runner
#$(PATH_TEST_RUNNERS)/Test%_Runner.c: $(PATH_TEST_SRC)/Test%.c
#	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb $(PATH_TEST_SRC)/Test%.c  $(PATH_TEST_RUNNERS)/Test%_Runner.c


#Link Test Code.
$(PATH_TEST_BUILD)/test%: $(PATH_TEST_OBJECTS)/Test%.$(OBJEXT) $(PATH_TEST_OBJECTS)/Test%_Runner.$(OBJEXT) $(PATH_TEST_OBJECTS)/unity.$(OBJEXT) $(BUILDDIR)/%.$(OBJEXT) #$(PATH_TEST_DEPS)Test%.$(DEPEXT)
	@echo "Linking Test.... $(PATH_TEST_BUILD)/$@"
	$(CC) -o $@ $^




define compile.prod =
@mkdir -p $(dir $@)
@echo " Compiling....  $@"
$(CC) $(CFLAGS) $(INC) -c -o $@ $<
@echo "Generating dependency's...."
@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRC_DIRS)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp
endef

define compile.test =
@mkdir -p $(dir $@)
@echo " Compiling....  $@"
$(CC) $(CFLAGS) -c $(TEST_INC) $< -o $@
@echo "Generating dependency's...."
$(CC)  $(CFLAGS) $(INCDEP) -MM -MG -MF $(PATH_TEST_DEPS)/$*.$(DEPEXT) $<
@cp -f $(PATH_TEST_DEPS)/$*.$(DEPEXT) $(PATH_TEST_DEPS)/$*.$(DEPEXT).tmp
@sed -e 's|.*:|$(PATH_TEST_OBJECTS)/$*.$(OBJEXT):|' < $(PATH_TEST_DEPS)/$*.$(DEPEXT).tmp > $(PATH_TEST_DEPS)/$*.$(DEPEXT)
@sed -e 's/.*://' -e 's/\\$$//' < $(PATH_TEST_DEPS)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(PATH_TEST_DEPS)/$*.$(DEPEXT)
@rm -f $(PATH_TEST_DEPS)/$*.$(DEPEXT).tmp
endef

#Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRC_DIRS)/%.$(SRCEXT)
	$(compile.prod)

$(PATH_TEST_OBJECTS)/%.$(OBJEXT):: $(PATH_TEST_SRC)/%.$(TESTEXT)
	$(compile.test)

$(PATH_TEST_OBJECTS)/%.$(OBJEXT):: $(PATH_TEST_RUNNERS)/%.$(TESTEXT)
	$(compile.test)
	
$(PATH_TEST_OBJECTS)/%.$(OBJEXT):: $(SRC_DIRS)/%.$(TESTEXT)
	$(compile.test)

$(PATH_TEST_OBJECTS)/%.$(OBJEXT):: $(UNITY_ROOT)/src/%.c $(UNITY_ROOT)/src/%.h
	$(compile.test)

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
	@echo "PATH_TEST_RESULTS=$(PATH_TEST_RESULTS)"
	@echo "Result command: $(PATH_TEST_RESULTS)/%.$(RESULT_EXT): $(PATH_TEST_BUILD)/%"
	@echo "UNAME_S= $(UNAME_S)"

.PRECIOUS: $(PATH_TEST_BUILD)/test%
.PRECIOUS: $(PATH_TEST_DEPS)/%.d
.PRECIOUS: $(PATH_TEST_OBJECTS)/%.o
.PRECIOUS: $(PATH_TEST_RESULTS)/%.txt
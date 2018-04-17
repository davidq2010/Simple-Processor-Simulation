# This Makefile should be in test directory

ifndef debug
	debug = 0
endif

# Directories
SRCDIR = ../src
UTILSDIR = $(SRCDIR)/../../utils
INCLDIR = $(SRCDIR)/../include

DEPFLAGS = -MP -MT $@ -MMD -MF $*.d
INCLFLAGS = -I$(INCLDIR)

# -L option says that static lib is in the folder immediately following it
# -l option says search library following it when linking
PROCLIBS = -L$(SRCDIR) -lproc

default:
	@echo No default target.

#include makefile defaults
include $(UTILSDIR)/makefile_defaults/Makefile.defaults

.PHONY: MAKE_PROC_LIBFILE
MAKE_PROC_LIBFILE:
	@echo Compiling Processor Library
	@cd $(SRCDIR); \
    $(MAKE) --no-print-directory debug=$(debug);

ifndef ECHO
  T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
    -nrRf $(firstword $(MAKEFILE_LIST)) \
  ECHO="COUNTTHIS" | grep -c "COUNTTHIS")

  N := x
  C = $(words $N)$(eval N := x $N)
  ECHO = echo "`expr " [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"
endif

TESTS = \
        testALU.o \
        testIntegration.o \
        testProcessor.o \
        testRegisterFile.o \
        testSignExtender.o \
        testSignExtenderAndMUX.o

.PHONY: all
all: $(TESTS)

testALU.o:                  MAKE_PROC_LIBFILE
testIntegration.o:          MAKE_PROC_LIBFILE
testProcessor.o:            MAKE_PROC_LIBFILE
testRegisterFile.o:         MAKE_PROC_LIBFILE
testSignExtender.o:         MAKE_PROC_LIBFILE
testSignExtenderAndMUX.o:   MAKE_PROC_LIBFILE

%.o: %.cpp
	$(GCC) $< $(CXXFLAGS) $(OPTS) $(DEPFLAGS) $(INCLFLAGS) $(PROCLIBS) -o $@
	cat $*.d >> Dependencies
	rm -f $*.d
	@$(ECHO) Linking $@
	@sleep 0.1
	@touch $@

# clean targets
CLEAN = $(TESTS)

.PHONY: reallyclean
reallyclean:
	@/bin/rm -f Dependencies
	@cd $(SRCDIR); $(MAKE) --no-print-directory clean

# Include the dependency files that exist; translate each file listed in src
# into its dependency file.
# wildcard omits dependency files that don't exist
-include Dependencies

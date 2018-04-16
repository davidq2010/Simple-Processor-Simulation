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
PARSLIBS = -L$(SRCDIR) -lpars
PARS_LIBFILE = $(SRCDIR)/libpars.a

default:
	@echo No default target.

#include makefile defaults
include $(UTILSDIR)/makefile_defaults/Makefile.defaults

.PHONY: MAKE_PARS_LIBFILE
MAKE_PARS_LIBFILE:
	@echo Compiling Parser Library
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
        testAssembler.o \
        testConfigParser.o \
        testMemoryParser.o

.PHONY: all
all: $(TESTS)

testAssembler.o:            MAKE_PARS_LIBFILE
testConfigParser.o:	    MAKE_PARS_LIBFILE
testMemoryParser.o:         MAKE_PARS_LIBFILE

%.o: %.cpp
	$(GCC) $< $(CXXFLAGS) $(OPTS) $(DEPFLAGS) $(INCLFLAGS) $(PARSLIBS) -o $@
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

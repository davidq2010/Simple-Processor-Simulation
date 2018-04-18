# This Makefile should be in test directory

ifndef debug
	debug = 0
endif

# Directories
UTILSDIR = ../utils
PROCSRC = ../processor/src
PARSSRC = ../parser/src
UTILSSRC = $(UTILSDIR)/src

UTILSINCL = $(UTILSDIR)/include
PROCINCL = $(PROCSRC)/../include
PARSINCL = $(PARSSRC)/../include

DEPFLAGS = -MP -MT $@ -MMD -MF $*.d
INCLFLAGS = -I$(PROCINCL) -I$(PARSINCL) -I$(UTILSINCL)

# -L option says that static lib is in the folder immediately following it
# -l option says search library following it when linking
PROCLIBS = -L$(PROCSRC) -lproc
PARSLIBS = -L$(PARSSRC) -lpars
UTILSLIBS = -L$(UTILSSRC) -lutils
LIBFLAGS = $(PROCLIBS) $(PARSLIBS) $(UTILSLIBS)

default: main.out

#include makefile defaults
include $(UTILSDIR)/makefile_defaults/Makefile.defaults

.PHONY: MAKE_PROC_LIBFILE
MAKE_PROC_LIBFILE:
	@echo Compiling Processor Library
	@cd $(PROCSRC); \
    $(MAKE) --no-print-directory debug=$(debug);

.PHONY: MAKE_PARS_LIBFILE
MAKE_PARS_LIBFILE:
	@echo Compiling Parser Library
	@cd $(PARSSRC); \
    $(MAKE) --no-print-directory debug=$(debug);

.PHONY: MAKE_UTILS_LIBFILE
MAKE_UTILS_LIBFILE:
	@echo Compiling utils Library
	@cd $(UTILSSRC); \
    $(MAKE) --no-print-directory debug=$(debug);

ifndef ECHO
  T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
    -nrRf $(firstword $(MAKEFILE_LIST)) \
  ECHO="COUNTTHIS" | grep -c "COUNTTHIS")

  N := x
  C = $(words $N)$(eval N := x $N)
  ECHO = echo "`expr " [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"
endif

main.out:				MAKE_PROC_LIBFILE MAKE_PARS_LIBFILE MAKE_UTILS_LIBFILE

%.out: %.cpp
	$(GCC) $< $(CXXFLAGS) $(OPTS) $(DEPFLAGS) $(INCLFLAGS) $(LIBFLAGS) -o $@
	@cat $*.d >> Dependencies
	@rm -f $*.d
	@$(ECHO) Linking $@
	@sleep 0.1
	@touch $@

# clean targets
CLEAN = main.out

.PHONY: reallyclean
reallyclean:
	$(MAKE) clean
	@/bin/rm -f Dependencies
	@cd $(PROCSRC); $(MAKE) --no-print-directory clean
	@cd $(PARSSRC); $(MAKE) --no-print-directory clean
	@cd $(UTILSSRC); $(MAKE) --no-print-directory clean

.PHONY: reallyreallyclean
reallyreallyclean:
	$(MAKE) reallyclean
	@cd $(PROCSRC); $(MAKE) --no-print-directory reallyclean
	@cd $(PARSSRC); $(MAKE) --no-print-directory reallyclean
	@cd $(UTILSSRC); $(MAKE) --no-print-directory reallyclean

# Include the dependency files that exist; translate each file listed in src
# into its dependency file.
# wildcard omits dependency files that don't exist
-include Dependencies

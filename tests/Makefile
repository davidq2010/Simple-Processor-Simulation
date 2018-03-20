# This Makefile should be in test directory

debug = 0

SRCDIR = ../src
INCDIR = ../include
DEPDIR := .d

GCC = g++
CXXFLAGS = -std=c++14 -Wall -Wno-deprecated -Werror -I$(INCDIR)
DEPFLAGS = -MP -MT $@ -MMD -MF $(DEPDIR)/$*.Td

# -L option says that static lib is in the folder immediately following it
# -l option says search library following it when linking
PROCLIBS = -L$(SRCDIR) -lproc
PROC_LIBFILE = $(SRCDIR)/libproc.a

default:
	@echo No default target.

.PHONY: MAKE_PROC_LIBFILE
MAKE_PROC_LIBFILE:
	@echo Compiling Processor Library
	@cd $(SRCDIR); \
    $(MAKE) --no-print-directory debug=$(debug);

# debug = 0 means no debugger
# -O3 is a bunch of optimizations
ifeq ($(debug), 0)
    OPTS = -O3
else
    OPTS = -ggdb -O0
endif

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
        testSignExtender.o \
        testSignExtenderAndMUX.o \
        testPartIntegration.o \
        testRegisterFile.o

.PHONY: all
all: $(TESTS)

testALU.o:                  MAKE_PROC_LIBFILE $(PROC_LIBFILE)
testSignExtender.o:         MAKE_PROC_LIBFILE $(PROC_LIBFILE)
testSignExtenderAndMUX.o:   MAKE_PROC_LIBFILE $(PROC_LIBFILE)
testPartIntegration.o:      MAKE_PROC_LIBFILE $(PROC_LIBFILE)
testRegisterFile.o:         MAKE_PROC_LIBFILE $(PROC_LIBFILE)

%.o: %.cpp
%.o: %.cpp $(DEPS)
	$(GCC) $< $(CXXFLAGS) $(OPTS) $(DEPFLAGS) $(PROCLIBS) -o $@
	@$(ECHO) Linking $@
	@sleep 0.1
	@touch $@

.PHONY: clean
clean:
	/bin/rm -f %.o

.PHONY: reallyclean
reallyclean:
	/bin/rm -f $(TESTS)
	/bin/rm -f $(DEPDIR)/*.d
	@cd $(SRCDIR); $(MAKE) --no-print-directory clean

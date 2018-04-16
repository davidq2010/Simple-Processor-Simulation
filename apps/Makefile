# This Makefile should be in apps directory

debug = 0

SRCDIR = ../src
INCDIR = ../include
DEPDIR := .d

GCC = g++
CXXFLAGS = -std=c++1y -Wall -Wno-deprecated -Werror -I$(INCDIR)
DEPFLAGS = -MP -MT $@ -MMD -MF $(DEPDIR)/$*.Td

# -L option says that static lib is in the folder immediately following it
# -l option says search library following it when linking
PROCLIBS = -L$(SRCDIR) -lproc
PROC_LIBFILE = $(SRCDIR)/libproc.a

all: $(APPS)

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

APPS = Processor

OBJECTS = \
          Integration.o

Integration.o:         MAKE_PROC_LIBFILE

$(shell mkdir -p $(DEPDIR))

Processor: Integration.o
	$(GCC) $< $(CXXFLAGS) -o $@
	@$(ECHO) Creating executable $@
	@sleep 0.1
	@touch $@

%.o: %.cpp
%.o: %.cpp $(DEPDIR)/%.d
	$(GCC) $< $(CXXFLAGS) -c $(OPTS) $(DEPFLAGS) $(PROCLIBS) -o $@
	@mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@
	@$(ECHO) Linking $@
	@sleep 0.1
	@touch $@

.PHONY: clean
clean:
	/bin/rm -f $(APPS)

# Create pattern rule with an empty recipe so make won't fail if dependency
# doesn't exist
$(DEPDIR)/%.d: ;

# Ensure make doesn't automatically delete these %.d files as intermediate files
.PRECIOUS: $(DEPDIR)/%.d

# Include the dependency files that exist; translate each file listed in src
# into its dependency file.
# wildcard omits dependency files that don't exist
include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCDIR))))

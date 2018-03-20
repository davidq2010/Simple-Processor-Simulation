# This Makefile should be in src directory

debug = 0

GCC = g++

# Directories
IDIR = ../include
SRCDIR = .
ODIR = ./obj
# Variables defined with := are expanded when defined rather than when used
DEPDIR := .d

# -MMD Generate dependency info as a side-effect of compilation, not instead of
# compilation. Omits system headers from dependencies.
# -MF $*.d write generated dependency file to temporary location
# -MT $@ sets the target name in the dependency file to the name left of the :
# -MP says to create .PHONY targets for all dependencies except for the primary
# .cpp file (MIGHT NOT WANT THIS, TEST IT)
DEPFLAGS = -MP -MT $@ -MMD -MF $(DEPDIR)/$*.Td
CXXFLAGS = -std=c++14 -Wall -Wno-deprecated -Werror -I$(IDIR)

# -L option says that static lib is in the folder immediately following it
# -l option says search library following it when linking
PROCLIBS = -L$(SRCDIR) -lproc
PROCLIBFILE = $(SRCDIR)/libproc.a

# debug = 0 means no debugger
# -O3 is a bunch of optimizations
ifeq ($(debug), 0)
  OPTS = -O3
else
  OPTS = -ggdb -O0
endif

# Prepend everything in _OBJS with ./obj/
_OBJS = ALU.o \
        MUX.o \
        ProcessorComponent.o \
        ProcessorUtil.o \
        RegisterFile.o \
        SignExtender.o
OBJS = $(patsubst %, $(ODIR)/%, $(_OBJS))

default: library

ifndef ECHO
  T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
    -nrRf $(firstword $(MAKEFILE_LIST)) \
    ECHO="COUNTTHIS" | grep -c "COUNTTHIS")
  N := x
  C = $(words $N)$(eval N := x $N)
  ECHO = echo -ne "\r [`expr $C '*' 100 / $T`%]"
endif

# @ at beginning of line says don't echo
# $< copies the first listed file right of colon
# -c says not to run linker.
# -c $< makes an object file out of %.cpp
# $@ sends the object file output into file with name on left of colon
# -o $@ says to put the result of the compilation into a file with the target
# name.
# By having a rule following the form *.o: *.cpp, the implicit build rules are
# disabled!!
# Will rebuild %.o if %.cpp or %.d change
$(ODIR)/%.o: %.cpp
$(ODIR)/%.o: %.cpp $(DEPDIR)/%.d
	$(GCC) $(CXXFLAGS) $(DEPFLAGS) $(OPTS) -c $< -o $@
  # Rename temporary dependency file to real dependency file. Do this in
  # separate step so failures during compilation won't leave corrupted
  # dependency file. Then, touch the file since some version of GCC might leave
  # object file older than dependency file, causing unnecessary rebuilds
	@mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@
	@$(ECHO) Compiling $@
	@sleep 0.1
	@touch $@


library: $(PROCLIBFILE)

# ar rcs means create archive file and run contents or something
$(PROCLIBFILE): $(OBJS)
	@$(ECHO) All done
	ar rcs $(PROCLIBFILE) $^

.PHONY: clean
clean:
	/bin/rm -f $(PROCLIBFILE)

.PHONY: reallyclean
reallyclean:
	@$(MAKE) clean
	/bin/rm -f $(OBJS)
	/bin/rm -f $(DEPDIR)/*.d

# Create pattern rule with an empty recipe so make won't fail if dependency
# doesn't exist
$(DEPDIR)/%.d: ;

# Ensure make doesn't automatically delete these %.d files as intermediate files
.PRECIOUS: $(DEPDIR)/%.d

# Include the dependency files that exist; translate each file listed in src
# into its dependency file.
# wildcard omits dependency files that don't exist
include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCDIR))))

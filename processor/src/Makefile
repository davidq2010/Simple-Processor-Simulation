# This Makefile should be in src directory

ifndef debug
	debug = 0
endif

# Directories
SRCDIR = .
ODIR = $(SRCDIR)/obj
UTILSDIR = $(SRCDIR)/../../utils
# Variables defined with := are expanded when defined rather than when used
INCLDIR = $(SRCDIR)/../include

# -MMD Generate dependency info as a side-effect of compilation, not instead of
# compilation. Omits system headers from dependencies.
# -MF $*.d write generated dependency file to temporary location
# -MT $@ sets the target name in the dependency file to the name left of the :
# -MP says to create .PHONY targets for all dependencies except for the primary
# .cpp file (MIGHT NOT WANT THIS, TEST IT)
DEPFLAGS = -MP -MT $@ -MMD -MF $*.d

# -I(dir) adds directory dir to head of list of directories to search for header
#  files
INCLFLAGS = -I$(INCLDIR)

PROCLIBFILE = $(SRCDIR)/libproc.a

# Prepend everything in _OBJS with ./obj/
_OBJS = ALU.o \
        ALUControl.o \
        ANDGate.o \
        Clock.o \
        Control.o \
        DataMemory.o \
        HardwiredConstant.o \
        InstructionMemory.o \
        Logger.o \
        MUX.o \
        Processor.o \
        ProcessorComponent.o \
        ProcessorUtil.o \
        ProgramCounter.o \
        RegisterFile.o \
        SignExtender.o

OBJS = $(patsubst %, $(ODIR)/%, $(_OBJS))

.PHONY: directories

default: directories library

directories: $(ODIR)

#include makefile defaults
include $(UTILSDIR)/makefile_defaults/Makefile.defaults

$(ODIR):
	@echo "Trying"
	@mkdir -p $@

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
# The -MMD flag will make the dependency file if it's changed.
# Will recompile if .cpp, .h, .o, or .d are changed
$(ODIR)/%.o: %.cpp
	$(GCC) $(CXXFLAGS) $(DEPFLAGS) $(INCLFLAGS) $(OPTS) -c $< -o $@
# This renames temporary dependency file to real dependency file. Does in
# separate step so failures during compilation won't leave corrupted
# dependency file. Then, touch the file since some version of GCC might leave
# object file older than dependency file, causing unnecessary rebuilds
	@cat $*.d >> Dependencies
	@rm -f $*.d
	@$(ECHO) Compiling $@
	@sleep 0.1
	@touch $@


library: $(PROCLIBFILE)

$(PROCLIBFILE): $(OBJS)
	@$(ECHO) Processor libfile ready
	$(AR) $(PROCLIBFILE) $^

# clean targets
CLEAN = $(PROCLIBFILE)

.PHONY: reallyclean
reallyclean:
	$(MAKE) clean
	/bin/rm -f $(OBJS)
	/bin/rm -f Dependencies

-include Dependencies

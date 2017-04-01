# IMPORTANT:
# 1. This Makefile was created for MinGW-w64 used on Windows 7 64-bit.
#    Because of this, it should be compatible with any other GCC port
#    for Windows, or even with Clang if using headers from MinGW, but one
#    should take into account that other versions of Windows could require
#    minimal modifications (see number 4).
#    Also, there's no guarantee it will work on other operating systems
#    or with other compilers than the ones mentioned so far, without proper
#    modifications of the whole Makefile.
# 2. This Makefile should be placed in parent directory of "src" folder.
# 3. By default, everywhere below by "directory" and "path" one should
#    understand the ones relative to root directory of the project.
# 4. Before using this Makefile, one should adjust
#    CXXINCLUDE, LDFLAGS, and LDLIBS variables, if necessary.

# Chosen shell.
SHELL = CMD

# Declaring file extensions.
SRCEXT = .cpp
HDREXT = .hpp
OBJEXT = .o
EXEEXT = .exe
DEPEXT = .d

.SUFFIXES:
.SUFFIXES: $(SRCEXT) $(OBJEXT)

# Build configuration, i.e. debug (the default one) or release.
# It influences compiler and linker flags, and objects and executables paths.
CONFIG = debug

# Chosen compiler; compiler flags.
CXX = clang++
CXXSTD = -std=c++14
CXXW = -Wall -Wextra -Wpedantic -Wshadow
CXXINCLUDE = \
-I"src" \
-I"D:/Programowanie/Biblioteki/cpp/Boost/include/boost-1_62"
ifeq "$(CONFIG)" "debug"
	CXXINCLUDE += -I"D:/Programowanie/Biblioteki/cpp/SFML-2.4.1/Debug/include"
  CXXOPTIMIZATION = -O0 -g
else \
ifeq "$(CONFIG)" "release"
	CXXINCLUDE += -I"D:/Programowanie/Biblioteki/cpp/SFML-2.4.1/Release/include"
  CXXOPTIMIZATION = -O3 -DNDEBUG
endif
CXXFLAGS = -c $(CXXOPTIMIZATION) $(CXXSTD) $(CXXW) $(CXXINCLUDE)

# Compiler flag responsible for the dependency generation.
DEPFLAGS = -MMD -MT $@ -MF $(@:$(OBJEXT)=$(DEPEXT))

# Linker flags.
LDFLAGS = \
-L"D:/Programowanie/Biblioteki/cpp/Boost/lib"
ifeq "$(CONFIG)" "debug"
	LDFLAGS += -L"D:/Programowanie/Biblioteki/cpp/SFML-2.4.1/Debug/lib"
	LDLIBS = -lboost_filesystem-mgw62-mt-d-1_62 -lboost_system-mgw62-mt-d-1_62 -lsfml-network-d -lsfml-system-d
else \
ifeq "$(CONFIG)" "release"
	LDFLAGS += -L"D:/Programowanie/Biblioteki/cpp/SFML-2.4.1/Release/lib"
	LDLIBS = -lboost_filesystem-mgw62-mt-1_62 -lboost_system-mgw62-mt-1_62 -lsfml-network -lsfml-system
endif

# Source code directories.
vpath %$(SRCEXT) src
vpath %$(HDREXT) src

# Directories of all objects and executable.
OBJDIR = $(CONFIG)/build
EXEDIR = $(CONFIG)/bin

# Paths of any single object, dependency file, and executable.
OBJNAMES = $(basename $(notdir $(shell dir src\*$(SRCEXT) /B /S)))
OBJ = $(addprefix $(OBJDIR)/,$(addsuffix $(OBJEXT),$(OBJNAMES)))

DEP = $(OBJ:$(OBJEXT)=$(DEPEXT))

EXENAME = client
EXE = $(addprefix $(EXEDIR)/,$(addsuffix $(EXEEXT),$(EXENAME)))

# Other variables.
DEL = del /F /S
MKDIR = mkdir $(subst /,\,$@)

# Fundamental rules.
$(EXE): $(OBJ) | $(EXEDIR)
	@echo.
ifndef ConEmuDir
	@echo "LINKING OBJECT FILES..."
else
	@cecho /cyan "Linking object files..."
endif
	$(CXX) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@
$(OBJDIR)/%$(OBJEXT): %$(SRCEXT) | $(OBJDIR)
	@echo.
	$(CXX) $< $(CXXFLAGS) $(DEPFLAGS) -o $@

-include $(DEP)

# Creating required directories.
$(EXEDIR):
	@echo.
	$(MKDIR)
$(OBJDIR):
	@echo.
	$(MKDIR)

# Phony targets.
.PHONY: clean clean_exe clean_build clean_obj clean_dep

clean: clean_exe clean_build

clean_exe:
	$(DEL) *$(EXEEXT)
clean_build: clean_obj clean_dep

clean_obj:
	$(DEL) *$(OBJEXT)
clean_dep:
	$(DEL) *$(DEPEXT)

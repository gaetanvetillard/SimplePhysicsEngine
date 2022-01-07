# Generic GNUMakefile
﻿MAKEFILE = gnu
CC = gcc
#debug options
DOPT = -Wall -g
#release options
ROPT = -Wall -o3 -D NDEBUG
#opt will get the release/debug config for the compiler
# change to $(DOPT) to produce debugable executable
OPT = $(ROPT)
#release exe name
EXE = spe.bin
#debug exe name
DEXE = spe_d.bin

#add all needed files here! (just C files not header)
SUBDIRS = Game/ Utils/
RDIR = ./
DDIR = ./

# Source files
GAM_SRC = $(wildcard Game/*.c)
UTI_SRC = $(wildcard Utils/*.c)
SRC = main.c Settings.c $(GAM_SRC) $(UTI_SRC)

# Headers Files
GAM_HDR = $(GAM_SRC:.c=.h)
UTI_HDR = $(UTI_SRC:.c=.h)
HDR = Settings.h $(GAM_HDR) $(UTI_HDR)

#object files for release version
GAM_OBJ = $(GAM_SRC:.c=.o)
UTI_OBJ = $(UTI_SRC:.c=.o)
OBJ = main.o Settings.o $(GAM_OBJ) $(UTI_OBJ)

#object files for debug version
GAM_DOBJ = $(GAM_SRC:.c=_d.o)
UTI_DOBJ = $(UTI_SRC:.c=_d.o)
DOBJ = main_d.o Settings_d.o $(GAM_DOBJ) $(UTI_DOBJ)

# List of the path to use when looking up for libraries
# modify path to match your target architecture ( x86 or x64), so it will link to the good library 
LIBPATH = 
# list of libraries to be linked dynamically
LIBS = -lm -lSDL2 `sdl2-config --libs` -lSDL2_image #-fopenmp

# recipes

# ------------
# release rules

.c.o:
	$(CC) $(ROPT) -c $(CFLAGS) $<

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(ROPT) $(INCPATH)  -o $@ $(OBJ) $(LIBPATH) $(LIBS)

%.o : %.c $(HDR)
	$(CC) $(ROPT) $(INCPATH) -c $< -o $@ $(LIBS)


# ------------
# Debug rule

debug: $(DEXE)

$(DEXE): $(DOBJ) $(HDR)
	$(CC) $(DOPT) $(INCPATH) -o $@ $(DOBJ) $(LIBPATH) $(LIBS)

%_d.o : %.c $(HDR)
	$(CC) $(DOPT) $(INCPATH)  -c $< -o $@ $(LIBS)

	
# -----------
# clean rule

clean:
	-rm $(OBJ) $(DOBJ)  2>/dev/null || true

	
	
	
# memo internal macro
# $@ --> The file name of the target of the rule.
# $^ --> he names of all the prerequisites, with spaces between them.
# $< The name of the first prerequisite.

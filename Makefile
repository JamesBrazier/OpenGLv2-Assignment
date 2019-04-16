# Author: J.P.Brazier, jbr185

# Definitions.
CXX = g++
CXXFLAGS = -g -DLINUX
DEL = rm
LDLIBS = -lm -lGL -lGLU -lglut


# Default target.
all: Assignment

Program.o: ${Program.cpp} ${./MyExtentions/MyExtentions.h} ${./TextureManager/TextureManager.h} ${./Objects/Objects.h}

# Target: program project.
.PHONY: program
Assignment: Program.o ${wildcard ./MyExtentions/*.cpp} ${wildcard ./TextureManager/*.cpp} ${wildcard ./Objects/*.cpp} 
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS) -O3
	${DEL} *.o

	
# Target: clean project.
.PHONY: clean
clean_all: 
	$(DEL) *.o *.out


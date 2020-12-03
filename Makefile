# Executable names:
EXE = final_project
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = graph.o main.o movies.o

# Generated files
CLEAN_RM = images/Out.png

# Use the cs225 makefile template:
include cs225/make/cs225.mk

#
# A simple makefile for compiling a c++ project
#

GCC=g++
VERSION_FLAGS = -std=c++17
DEPS = parser.h
CFLAGS=-I.
OBJ = parser.o

%.o: %.cc $(DEPS)
	g++ -std=c++14 -c -o $@ $< $(CFLAGS)

out: $(OBJ)
	g++ -std=c++14 main.cpp -o $@ $^ $(CFLAGS)

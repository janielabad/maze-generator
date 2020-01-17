# Makefile for disjoint sets + maze project

CC = g++ -g -Wall -Wextra -pedantic -std=c++11
DEPS = disjointSets.h mazeGenerator.h
OBJS = testDSclass.o disjointSets.o mazeGenerator.o maze.o

all: testDSclass maze

disjointSets.o: disjointSets.cpp disjointSets.h
	$(CC) -c disjointSets.cpp

testDSclass: testDSclass.o disjointSets.o disjointSets.h
	$(CC) -o testDSclass testDSclass.o disjointSets.o

testDSclass.o: testDSclass.cpp disjointSets.h
	$(CC) -c testDSclass.cpp

mazeGenerator.o: mazeGenerator.cpp disjointSets.h mazeGenerator.h
	$(CC) -c mazeGenerator.cpp

maze.o: maze.cpp mazeGenerator.o disjointSets.o
	$(CC) -c maze.cpp

maze: maze.o mazeGenerator.o disjointSets.o
	$(CC) -o maze maze.o mazeGenerator.o disjointSets.o

# -----
# clean by removing object files

clean:
	rm $(OBJS)

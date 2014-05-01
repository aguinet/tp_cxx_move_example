CXX=g++
CC=g++
CXXFLAGS=-O3 -g -std=c++11 -Wall -Wextra
LDFLAGS=

move: move.o

clean:
	rm *.o
	rm move

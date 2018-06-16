#sim6502 practice project makefile
INCLUDEPATH := include

SRCPATH := src

CXXFLAGS := -std=c++1z -Werror -Wall -Wextra

all: build
	g++ src/simulate.cpp $(CXXFLAGS) -I$(INCLUDEPATH) -o build/simulate
	
build:
	mkdir build
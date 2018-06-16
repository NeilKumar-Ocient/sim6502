#sim6502 practice project makefile
INCLUDEPATH := include
SRCPATH := src
BUILDPATH := build

CXXFLAGS := -std=c++1z -Werror -Wall -Wextra

.PHONY: all
all: build
	g++ src/cpu.cpp $(CXXFLAGS) -I$(INCLUDEPATH) -c -o $(BUILDPATH)/cpu.o
	g++ src/simulate.cpp $(CXXFLAGS) -I$(INCLUDEPATH) -o $(BUILDPATH)/simulate $(BUILDPATH)/cpu.o

.PHONY: clean
clean: build
	cd $(BUILDPATH) && rm -rf *
	
$(BUILDPATH):
	mkdir $(BUILDPATH)
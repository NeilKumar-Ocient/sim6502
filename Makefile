#sim6502 practice project makefile

all: build
	g++ src/simulate.cpp -o build/simulate
	
build:
	mkdir build
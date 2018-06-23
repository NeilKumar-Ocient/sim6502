#sim6502 practice project makefile
INCLUDE_PATH := include
SRC_PATH := src
BUILD_PATH := build

#build flags
#RELEASE=y causes the RELEASE and NDEBUG flags to be defined, as well as o2
ifdef RELEASE
OLEVEL = 2
CXX_EXTRA_DEFINES := $(CXX_EXTRA_DEFINES) RELEASE NDEBUG
endif

#NO_CLOCK=y causes the NO_CLOCK flag to be defined, which turns off slow cycles from killing the program
ifdef NO_CLOCK
CXX_EXTRA_DEFINES := $(CXX_EXTRA_DEFINES) NO_CLOCK
endif

#define cxx flags
CXXFLAGS := -std=c++1z -Werror -Wall -Wextra -I$(INCLUDE_PATH)
ifdef CXX_EXTRA_DEFINES
CXXFLAGS := $(CXXFLAGS) $(foreach d, $(CXX_EXTRA_DEFINES), -D$(d))
endif
ifdef OLEVEL
CXXFLAGS := $(CXXFLAGS) -O$(OLEVEL)
endif

.PHONY: all
all: build
	g++ src/cpu.cpp $(CXXFLAGS) -c -o $(BUILD_PATH)/cpu.o
	g++ src/simulate.cpp $(CXXFLAGS) -o $(BUILD_PATH)/simulate $(BUILD_PATH)/cpu.o

.PHONY: clean
clean: build
	cd $(BUILD_PATH) && rm -rf *
	
$(BUILD_PATH):
	mkdir $(BUILD_PATH)
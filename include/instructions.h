#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "cpu.h"

//all of the possible address modes, used to template the instructions
enum addressMode_t {
	ZERO_PAGE = 0,
	INDEXED_ZERO_PAGE = 1,
	ABSOLUTE = 2,
	INDEXED_ABSOLUTE = 3,
	INDIRECT = 4,
	IMPLIED = 5,
	ACCUMULATOR = 7,
	IMMEDIATE = 8,
	RELATIVE = 9,
	INDEXED_INDIRECT = 10,
	INDIRECT_INDEXED = 11
};

//TODO write the instructions themselves
/*instructions will have a function signature as follows, they return the new value of the stack pointer after the instruction
 * it is also the instructions responsibility to call cycle() on the cpu after what would be 1 cycle of work
 * template<addressMode_t MODE>
 * uint16_t instructionName(cpu_t* cpu)
 * */

#endif

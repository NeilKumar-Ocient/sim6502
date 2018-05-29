#include "cpu.h"
#include "instructions.h"

uint8_t cpu_t::run() {
	//start the clock, then enter a loop to repeatedly execute the instruction at the program counter
	m_clock.start();

	//TODO when do we finish the program?
	while(true) {
		//TODO am i allowed to create a variable here or do i need to put the opCode in some register or push it on the stack or something
		//read the instruction at the program counter, and finish a cycle
		uint8_t opCode = m_mmu.read(m_pc);
		cycle();

		//execute the instruction
		m_pc = executeInstruction(opCode);
	}

	return 0;
}

uint16_t cpu_t::executeInstruction(uint8_t opCode) {
	//TODO switch based on the opCode to run the correct instruction
	return 0;
}

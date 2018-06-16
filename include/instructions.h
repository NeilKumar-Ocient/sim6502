#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "cpu.h"

//TODO may want to aggressively inline all of these
//all of the possible address modes, used to template the instructions
enum addressMode_t {
	ZERO_PAGE = 0,
	ZERO_PAGE_X = 1,
	ZERO_PAGE_Y = 2,
	ABSOLUTE = 3,
	ABSOLUTE_X = 4,
	ABSOLUTE_Y = 5,
	INDIRECT = 6,
	IMPLIED = 7,
	ACCUMULATOR = 8,
	IMMEDIATE = 9,
	RELATIVE = 10,
	INDIRECT_X = 11,
	INDIRECT_Y = 12
};

/*
 * Arithmetic Instructions
 */

//add with carry
template<addressMode_t MODE>
uint16_t ADC(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//subtract with carry
template<addressMode_t MODE>
uint16_t SBC(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//arithmetic shift left
template<addressMode_t MODE>
uint16_t ASL(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//logical shift right
template<addressMode_t MODE>
uint16_t LSR(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//rotate left
template<addressMode_t MODE>
uint16_t ROL(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//rotate right
template<addressMode_t MODE>
uint16_t ROR(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//bitwise and with accumulator
template<addressMode_t MODE>
uint16_t AND(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//bitwise or with accumulator
template<addressMode_t MODE>
uint16_t ORA(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//bitwise exclusive or
template<addressMode_t MODE>
uint16_t EOR(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//decrement memory
template<addressMode_t MODE>
uint16_t DEC(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//increment memory
template<addressMode_t MODE>
uint16_t INC(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

/*
 * Register Instructions
 */

//store accumulator
template<addressMode_t MODE>
uint16_t STA(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//store X register
template<addressMode_t MODE>
uint16_t STX(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//store Y register
template<addressMode_t MODE>
uint16_t STY(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//load accumulator
template<addressMode_t MODE>
uint16_t LDA(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//load X register
template<addressMode_t MODE>
uint16_t LDX(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//load Y register
template<addressMode_t MODE>
uint16_t LDY(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//transfer A to X
template<addressMode_t MODE>
uint16_t TAX(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//transfer X to A
template<addressMode_t MODE>
uint16_t TXA(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//decrement X
template<addressMode_t MODE>
uint16_t DEX(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//increment X
template<addressMode_t MODE>
uint16_t INX(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//transfer A to Y
template<addressMode_t MODE>
uint16_t TAY(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//transfer Y to A
template<addressMode_t MODE>
uint16_t TYA(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//decrement Y
template<addressMode_t MODE>
uint16_t DEY(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//increment Y
template<addressMode_t MODE>
uint16_t INY(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//compare accumulator
template<addressMode_t MODE>
uint16_t CMP(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//compare X register
template<addressMode_t MODE>
uint16_t CPX(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//compare Y register
template<addressMode_t MODE>
uint16_t CPY(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

/*
 * Flag Instructions
 */

//clear carry
template<addressMode_t MODE>
uint16_t CLC(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//set carry
template<addressMode_t MODE>
uint16_t SEC(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//clear interrupt
template<addressMode_t MODE>
uint16_t CLI(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//set interrupt
template<addressMode_t MODE>
uint16_t SEI(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//clear overflow
template<addressMode_t MODE>
uint16_t CLV(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//clear decimal
template<addressMode_t MODE>
uint16_t CLD(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//set decimal
template<addressMode_t MODE>
uint16_t SED(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

/*
 * Branch Instructions
 */

//branch on plus
template<addressMode_t MODE>
uint16_t BPL(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//branch on minus
template<addressMode_t MODE>
uint16_t BMI(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//branch on overflow clear
template<addressMode_t MODE>
uint16_t BVC(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//branch on overflow set
template<addressMode_t MODE>
uint16_t BVS(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//branch on carry clear
template<addressMode_t MODE>
uint16_t BCC(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//branch on carry set
template<addressMode_t MODE>
uint16_t BCS(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//branch on not equal
template<addressMode_t MODE>
uint16_t BNE(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//branch on equal
template<addressMode_t MODE>
uint16_t BEQ(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//break
template<addressMode_t MODE>
uint16_t BRK(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//jump
template<addressMode_t MODE>
uint16_t JMP(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//jump to subroutine
template<addressMode_t MODE>
uint16_t JSR(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//return from interrupt
template<addressMode_t MODE>
uint16_t RTI(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//return from subroutine
template<addressMode_t MODE>
uint16_t RTS(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

/*
 * Stack Instructions
 */

//transfer X to stack pointer
template<addressMode_t MODE>
uint16_t TXS(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//transfer stack pointer to X
template<addressMode_t MODE>
uint16_t TSX(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//push accumulator
template<addressMode_t MODE>
uint16_t PHA(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//pull accumulator
template<addressMode_t MODE>
uint16_t PLA(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//push processor status
template<addressMode_t MODE>
uint16_t PHP(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//pull processor status
template<addressMode_t MODE>
uint16_t PLP(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

/*
 * Other Instructions
 */

//test bits
template<addressMode_t MODE>
uint16_t BIT(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

//no operation
template<addressMode_t MODE>
uint16_t NOP(cpu_t* cpu) {
	//TODO
	return cpu->getPc();
}

#endif

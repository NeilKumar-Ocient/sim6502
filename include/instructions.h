#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "cpu.h"

//TODO may want to aggressively inline all of these
//all of the possible address modes, used to template the instructions
enum addressMode_t {
	ZERO_PAGE = 0, //pc += 2
	ZERO_PAGE_X = 1, //pc += 2
	ZERO_PAGE_Y = 2, //pc += 2
	ABSOLUTE = 3, //pc += 3
	ABSOLUTE_X = 4, //pc += 3
	ABSOLUTE_Y = 5, //pc += 3
	INDIRECT = 6, // pc += 3
	IMPLIED = 7, //pc += 1
	ACCUMULATOR = 8, //pc += 1
	IMMEDIATE = 9, //pc += 2
	RELATIVE = 10, //pc += 2 + bb, where bb is the value at pc + 1
	INDIRECT_X = 11, //pc += 2
	INDIRECT_Y = 12 // pc += 2
};

//the amount that the pc gets incremented for each address mode, some require extra logic on top of this like relative
static constexpr std::array<uint8_t, 13> PC_INCREMENTS = {2, 2, 2, 3, 3, 3, 3, 1, 1, 2, 2, 2, 2};

//a function that reads certain addresses based on the addressing mode, and fills in a general struct that contains arguments for all instructions/addressing modes
struct args_t {
	args_t() : m_arg1(0) {}
	//TODO what else needs to go in here?
	uint8_t m_arg1;
};

//a helper function that fills in an arguments struct based on the different addressing modes, used to reduce code copying
template<addressMode_t MODE>
args_t getArgs(cpu_t* cpu) {
	args_t args;
	/*
     *zero page case, arg is the value of mem[ mem[pc + 1] ]
     */
    if constexpr(MODE == addressMode_t::ZERO_PAGE) {
		//read pc + 1
		uint8_t zeroOffset = cpu->read(cpu->getPc() + 1);
		cpu->cycle();
		assert(cpu->getPc() + 1 < 256); //just a sanity check
		//get the value there and store that as the argument
		args.m_arg1 = cpu->read(zeroOffset);
		cpu->cycle();
	}
    /*
     * Zero page X: arg is the value of mem[ mem[pc + 1] + X ]
     */
    if constexpr(MODE == addressMode_t::ZERO_PAGE_X) {
        //zero offset is MEM[ MEM[pc + 1] + X] register
        uint8_t zeroOffset = cpu->read(cpu->getPc() + 1) + cpu->getX();
        cpu->cycle();
        assert(cpu->getPc() + 1 < 256); //sanity check
        args.m_arg1 = cpu->read(zeroOffset);
        cpu->cycle();
    }
    /*
     * Zero Page Y: arg is the value of mem[ mem[pc + 1] + Y ]
     */
    if constexpr(MODE == addressMode_t::ZERO_PAGE_Y) {
        //zero offset is MEM[ MEM[pc + 1] + Y ]
        uint8_t zeroOffset = cpu->read(cpu->getPc() + 1) + cpu->getY();
        cpu->cycle();
        assert(cpu->getPc() + 1 < 256);//sanity check
        args.m_arg1 = cpu->read(zeroOffset);
        cpu->cycle();
    }
    /*
     * Absolute: data to operate on is in 2 operands supplied, LSB first MEM[ MEM[ PC + 2 ] :: MEM[ PC + 1] ]
     */
    if constexpr(MODE == addressMode_t::ABSOLUTE) {
        uint16_t addressToAccess = cpu->read(cpu->getPc() + 1);
        addressToAccess = addressToAccess & (cpu->read(cpu->getPc() +1) << 8);
        cpu->cycle();
        assert(cpu->getPc() + 1 < 256);
        args.m_arg1 = cpu->read(addressToAccess);
        cpu->cycle();
    }

	//TODO write the rest of the cases
    return args;
}

//a helper function that returns the new pc given the current pc, depends on addressing mode
//for the relative mode, relativeArg is the additional value to be added if the branch was taken
template<addressMode_t MODE>
uint16_t getNewPc(uint16_t pc, int8_t relativeArg = 0) {
	uint16_t newPc = pc + PC_INCREMENTS[MODE];
	if constexpr(MODE == addressMode_t::RELATIVE) {
		newPc = static_cast<int16_t>(newPc) + relativeArg;
	}
	return newPc;
}

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
	args_t args = getArgs<MODE>(cpu);
	cpu->setA(cpu->getA() & args.m_arg1);
	return getNewPc<MODE>(cpu->getPc());
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

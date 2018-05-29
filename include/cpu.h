#ifndef CPU_H
#define CPU_H

#include "cpuClock.h"
#include "mmu.h"
#include <vector>

static constexpr uint16_t stackOffset = 256;
static constexpr size_t smallProgramSize = addressSpaceSize / 4;
static constexpr size_t bigProgramSize = smallProgramSize * 2;
static constexpr size_t programOffset = addressSpaceSize / 2;
static constexpr size_t cpuClockFrequency =  1789772500 //the clock frequency for the cpu in mHz, not in Hz b/c we want to run at a fraction of a Hz without using a double

//flag enum
enum flag_t {
	CARRY = 0,
	ZERO = 1,
	INTERUPT_DISABLE = 2,
	DECIMAL = 3,
	BREAK = 4,
	OVERFLOW = 5,
	NEGATIVE = 6
};

//flag bit masks
static constexpr uint8_t carryMask = 0x01;
static constexpr uint8_t zeroMask = 0x02;
static constexpr uint8_t interuptDisbleMask = 0x04;
static constexpr uint8_t decimalMask = 0x08;
static constexpr uint8_t breakMask = 0x10;
static constexpr uint8_t overflowMask = 0x20;
static constexpr uint8_t negativeMask = 0x40;

//the cpu, this is responsible for reading program instructions and executing them
class cpu_t {
public:
	//constructor, takes in an either 16K or 32K program and loads that into the higher memory addresses
	//if a 16k program is passed in we load that into memory twice so that the high 32k is always used
	cpu_t(const std::vector<uint8_t>& program) : m_clock(cpuClockFrequency),
		m_pc(0), m_sp(255), m_a(0), m_x(0), m_y(0), m_flags(0)
	{
			if(program.size() == smallProgramSize) {
				//load the small program twice
				for(size_t i = 0; i < 2; ++i) {
					for(size_t j = 0; j < smallProgramSize; ++j) {
						m_mmu.write(programOffset + (i * smallProgramSize) + j, program[j]);
					}
				}
			}
			else if(program.size() == bigProgramSize) {
				//load the big program
				for(size_t i = 0; i < bigProgramSize; ++i) {
					m_mmu.write(programOffset + i, program[i]);
				}
			}
			else {
				//only these 2 sizes are allowed
				throw;
			}
	}

	//copy/move constructor/assignment deleted
	cpu_t(const cpu_t& rhs) = delete;
	cpu_t(cpu_t&& rhs) = delete;
	cpu_t& operator=(const cpu_t& rhs) = delete;
	cpu_t& operator=(cpu_t&& rhs) = delete;

	//TODO not really sure how to determine when a program ends and what it returns
	//runs the program
	uint8_t run();

	//functions to interact with the registers
	uint8_t getA() {
		return m_a;
	}

	void setA(uint8_t value) {
		m_a = value;
	}

	uint8_t getX() {
		return m_x;
	}

	void setX(uint8_t value) {
		m_x = value;
	}

	uint8_t getY() {
		return m_y;
	}

	void setY(uint8_t value) {
		m_y = value;
	}

	//gets the given flag
	template<flag_t FLAG>
	bool getFlag() {
		if constexpr(FLAG == flag_t::CARRY) {
			return (m_flag & carryMask) == carryMask;
		}
		else if constexpr(FLAG == flat_t::ZERO) {
			return (m_flag & zeroMask) == zeroMask;
		}
		else if constexpr(FLAG == flat_t::INTERUPT_DISABLE) {
			return (m_flag & interuptDisableMAsk) == interuptDisableMask;
		}
		else if constexpr(FLAG == flat_t::DECIMAL) {
			return (m_flag & decimalMask) == decimalMAsk;
		}
		else if constexpr(FLAG == flat_t::BREAK) {
			return (m_flag & breakMask) == breakMask;
		}
		else if constexpr(FLAG == flat_t::OVERFLOW) {
			return (m_flag & overflowMask) == overflowMask;
		}
		else if constexpr(FLAG == flat_t::NEGATIVE) {
			return (m_flag & negativeMask) == negativeMask;
		}
		else {
			//not possible
			throw;
		}
	}

	//sets the given flag
	template<flag_t FLAG>
	void setFlag() {
		if constexpr(FLAG == flag_t::CARRY) {
			m_flag |= carryMask;
		}
		else if constexpr(FLAG == flat_t::ZERO) {
			m_flag |= zeroMask;
		}
		else if constexpr(FLAG == flat_t::INTERUPT_DISABLE) {
			m_flag |= interuptDisableMask;
		}
		else if constexpr(FLAG == flat_t::DECIMAL) {
			m_flag |= decimalMask;
		}
		else if constexpr(FLAG == flat_t::BREAK) {
			m_flag |= breakMask;
		}
		else if constexpr(FLAG == flat_t::OVERFLOW) {
			m_flag |= overflowMask;
		}
		else if constexpr(FLAG == flat_t::NEGATIVE) {
			m_flag |= negativeMask;
		}
		else {
			//not possible
			throw;
		}
	}

	//TODO maybe consider giving ~mask their own constexpr to save time if needed
	//clears the given flag
	template<flag_t FLAG>
	void clearFlag() {
		if constexpr(FLAG == flag_t::CARRY) {
			m_flag &= ~carryMask
		}
		else if constexpr(FLAG == flat_t::ZERO) {
			m_flag &= ~zeroMask
		}
		else if constexpr(FLAG == flat_t::INTERUPT_DISABLE) {
			m_flag &= ~interuptDisableMask
		}
		else if constexpr(FLAG == flat_t::DECIMAL) {
			m_flag &= ~decimalMask
		}
		else if constexpr(FLAG == flat_t::BREAK) {
			m_flag &= ~breakMask
		}
		else if constexpr(FLAG == flat_t::OVERFLOW) {
			m_flag &= ~overflowMask
		}
		else if constexpr(FLAG == flat_t::NEGATIVE) {
			m_flag &= ~negativeMask
		}
		else {
			//not possible
			throw;
		}
	}

	void pushStack(uint8_t value) {
		//push the given value onto the stack and decrement the stack register
		m_mmu.write(stackOffset + m_sp--, value);
	}

	uint8_t pullStack() {
		//return the current value on the stack and increment the stack register
		return m_mmu.read(stackOffset + m_sp++);
	}

	//there is only a get for the program counter
	//the program counter gets updated based on the return value of the instructions
	uint16_t getPc() {
		return m_pc;
	}

	//calls cycle() on the clock to notify that 1 clock cycle of work has occurred
	void cycle() {
		m_clock.cycle();
	}

private:
	//the clock and mmu
	cpuClock_t m_clock;
	mmu_t m_mmu;

	//the registers
	uint16_t m_pc;
	uint8_t m_sp;
	uint8_t m_a;
	uint8_t m_x;
	uint8_t m_y;
	uint8_t m_flags;

	uint16_t executeInstruction(uint8_t opCode);
};

#endif

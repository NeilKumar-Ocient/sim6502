#ifndef MMU_H
#define MMU_H

#include <array>

static constexpr size_t addressSpaceSize = 1024 * 64;

//the mmu, responsible for holding and reading from / writing to memory
//also handles memory redirects of various kinds including port IO
//also handles invalid permissions to read/write addresses
class mmu_t {
public:
	//constructor
	mmu_t() {
		m_mem.fill(0); //fill the memory initially with all 0
	}

	//no copy/move constuctor/assignment
	mmu_t(const mmu_t& rhs) = delete;
	mmu_t(mmu_t&& rhs) = delete;
	mmu_t& operator=(const mmu_t& rhs) = delete;
	mmu_t& operator=(mmu_t&& rhs) = delete;

	//read
	uint8_t read(uint16_t address) {
		//TODO eventually handle internal redirects, port IO redirects, and permissions
		return m_mem[address];
	}

	void write(uint16_t address, uint8_t value) {
		//TODO eventually handle internal redirects, port IO redirects, and permissions
		m_mem[address] = value;
	}
private:
	std::array<uint8_t, addressSpaceSize> m_mem; //the memory itself, always 64k in size
};

#endif

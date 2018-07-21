#include "cpu.h"
#include <thread>

int main() {
	//just testing for compilation
	std::vector<uint8_t> program(BIG_PROGRAM_SIZE, 0);
	cpu_t cpu(program, "cpu.log");
	std::thread cpuThread(&cpu_t::run, &cpu, 0);
	cpuThread.join();
	return 0;
}

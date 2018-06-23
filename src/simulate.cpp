#include "cpu.h"

int main() {
	//just testing for compilation
	std::vector<uint8_t> program(bigProgramSize, 0);
	cpu_t cpu(program, "cpu.log");
	cpu.run();

	return 0;
}

#include "Cpu.h"

int main()
{
	Bios bios(".\\scph1001.bin");
	Interconnect inter(&bios);
	Cpu cpu(&inter);
	std::cout << std::hex << cpu.regs[1] << std::endl;
	while (true)
	{
		cpu.run_next_instruction();
	}


	return 0;
}
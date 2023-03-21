#include "Interconnect.h"

Interconnect::Interconnect(Bios* pbios)
{
	bios = pbios;
}
Interconnect::~Interconnect(){}

uint32_t Interconnect::load32(uint32_t addr)
{
	uint32_t abs_addr = map::mask_region(addr);

	if (map::BIOS.contains(abs_addr))
	{
		uint32_t offset = abs_addr - map::BIOS.start;
		return(bios->load32(offset));
	}
	else if (map::RAM.contains(abs_addr))
	{
		uint32_t offset = abs_addr - map::RAM.start;
		return(ram.load32(offset));
	}
	else if (map::CACHE_CONTROL.contains(abs_addr))
	{
		std::cout << "!!!!!!!!!!!!!Ignoring store to CACHE_CONTROL address: " << std::hex << abs_addr << std::endl;
		return 0;
	}

	else
		std::cout << "Error in fetch32 from address: " << std::hex << addr << std::endl;
}
void Interconnect::store32(uint32_t addr, uint32_t value)
{
	if ((addr % 4) != 0)
	{
		std::cout << "Unaligned store32@@@ to address: " << std::hex << addr << std::endl;
		return;
	}
	uint32_t abs_addr = map::mask_region(addr);
	std::cout << "Stroing store32@@@ to address: " << std::hex << addr << std::endl;

	if		(map::SYS_CONTROL.contains(abs_addr))
	{
		uint32_t offset = abs_addr - map::SYS_CONTROL.start;
		switch (offset)
		{
		case 0:
			if (value != 0x1f000000) {
				std::cout << "Bad expansion 1 base address: " << std::hex << value << std::endl;
			}
			break;
		case 4:
			if (value != 0x1f802000) {
				std::cout << "Bad expansion 2 base address: " << std::hex << value << std::endl;
			}
			break;
		default:
			std::cout << "Unhandled write to MEM_CONTROL" << std::endl;
			break;
		}
	}
	else if (map::RAM_SIZE.contains(abs_addr))
	{
		std::cout << "Ignoring store to RAM_SIZE address: " << std::hex << abs_addr << std::endl;
	}
	else if (map::CACHE_CONTROL.contains(abs_addr))
	{
		std::cout << "Ignoring store to CACHE_CONTROL address: " << std::hex << abs_addr << std::endl;
	}
	else if (map::RAM.contains(abs_addr))
	{
		uint32_t offset = abs_addr - map::RAM.start;
		ram.store32(offset, value);
	}
	else
		std::cout << "Unhandled store32 to address: " << std::hex << abs_addr << std::endl;
}
void Interconnect::store16(uint32_t addr, uint16_t value)
{
	if ((addr % 2) != 0)
	{
		std::cout<< "Unaligned store16 to address: " << std::hex << addr << std::endl;
		return;
	}
	uint32_t abs_addr = map::mask_region(addr);
	if (map::SPU.contains(abs_addr))
	{
		uint32_t offset = abs_addr - map::SPU.start;
		std::cout << "Unhandled write16 to SPU register: " << std::hex << offset << std::endl;
		return;
	}
	std::cout << "Unhandled store16 to address: " << std::hex << addr << std::endl;
}

void Interconnect::store8(uint32_t addr, uint8_t value)
{
	std::cout << " - i handled it - store 8";
	uint32_t abs_addr = map::mask_region(addr);
	if (map::EXPANSION_2.contains(abs_addr))
	{
		uint32_t offset = abs_addr - map::EXPANSION_2.start;
		std::cout << "Unhandled write8 to expansion2 register: " << std::hex << offset << std::endl;
		return;
	}
	std::cout << "Unhandled store8 to address: " << std::hex << addr << std::endl;
}

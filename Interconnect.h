#pragma once
#include "Bios.h"
#include "Range.h"
#include "Ram.h"

class Interconnect
{
public:
	Interconnect(Bios* pbios);
	~Interconnect();

public:
	Bios* bios;
	Ram ram;

public:
	uint32_t load32(uint32_t addr);
	void store32(uint32_t addr, uint32_t value);
	void store16(uint32_t addr, uint16_t value);
	void store8(uint32_t addr, uint8_t value);
};


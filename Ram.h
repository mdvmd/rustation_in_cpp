#pragma once
#include <vector>
#include <cstdint>

class Ram
{
public:
	Ram();
	~Ram();

public:
	std::vector<uint8_t> data;

public:
	uint32_t load32(uint32_t offset);
	void store32(uint32_t offset, uint32_t value);
};


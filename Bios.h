#pragma once
#include <vector>
#include <string>
#include <iostream>

class Bios
{
public:
	Bios(std::string path);
	~Bios();

public:
	std::vector<uint8_t> data;
	constexpr static uint64_t BIOS_SIZE = 512 * 1024;

public:
	uint32_t load32(uint32_t offset);
};


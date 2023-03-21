#pragma once
#include <cstdint>

namespace map {
	class Range
	{
	public:
		Range(uint32_t s, uint32_t l);
		~Range();

	public:
		uint32_t start, length;

	public:
		bool contains(uint32_t addr);
	};

	static Range RAM = Range(uint32_t(0x00000000), 2 * 1024 * 1024);
	static Range BIOS = Range(uint32_t(0x1fc00000), 512*1024);
	static Range SYS_CONTROL = Range(uint32_t(0x1f801000), 36);
	static Range RAM_SIZE = Range(uint32_t(0x1f801060), 4);
	static Range SPU = Range(uint32_t(0x1f801c00), 640);
	static Range EXPANSION_2 = Range(uint32_t(0x1f802000), 66);

	static Range CACHE_CONTROL = Range(uint32_t(0xfffe0130), 4);

	static constexpr uint32_t REGION_MASK[8] = { 0xffffffff,0xffffffff, 0xffffffff,
		0xffffffff, 0x7fffffff, 0x1fffffff, 0xffffffff, 0xffffffff,
	};


	uint32_t mask_region(uint32_t addr);
}


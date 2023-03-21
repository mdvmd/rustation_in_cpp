#include "Ram.h"

Ram::Ram()
{
	uint32_t RAM_SIZE = 2 * 1024 * 1024;
	for (int i = 0; i < RAM_SIZE; i++)
		data.push_back(0x00);
}

Ram::~Ram()
{
}

uint32_t Ram::load32(uint32_t offset)
{
	uint32_t b0 = data[offset + 0];
	uint32_t b1 = data[offset + 1];
	uint32_t b2 = data[offset + 2];
	uint32_t b3 = data[offset + 3];

	uint32_t complete_word = b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
	return complete_word;
}

void Ram::store32(uint32_t offset, uint32_t value)
{
	uint8_t b0 = value & 0xff;
	uint8_t b1 = (value >> 8) & 0xff;
	uint8_t b2 = (value >> 16) & 0xff;
	uint8_t b3 = (value >> 24) & 0xff;
	data[offset + 0] = b0;
	data[offset + 1] = b1;
	data[offset + 2] = b2;
	data[offset + 3] = b3;
}

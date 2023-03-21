#include "Range.h"

map::Range::Range(uint32_t s, uint32_t l)
{
	start = s;
	length = l;
}
map::Range::~Range(){}

bool map::Range::contains(uint32_t addr)
{
	if (addr >= start && addr < (start + length))
	{
		return true;
	}
	else
		return false;
}
uint32_t map::mask_region(uint32_t addr) {
	uint32_t index = (addr >> 29);
	return (addr & REGION_MASK[index]);
}
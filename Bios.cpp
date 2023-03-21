#include "Bios.h"
#include <fstream>


Bios::Bios(std::string path) {
	std::ifstream file(path, std::ios::binary);
	if (file)
	{
		file.seekg(0, std::ios::end);
		std::streampos fileSize = file.tellg();
		file.seekg(0, std::ios::beg);
		if (fileSize == BIOS_SIZE)
		{
			data.resize(fileSize);
			file.read(reinterpret_cast<char*>(data.data()), fileSize);
			std::cout << "Size of Vec BIOS " << data.size() << std::endl;
		}
		else
		{
			std::cout << "Not right size of BIOS" << std::endl;
			return;
		}
	}

}

Bios::~Bios(){}

uint32_t Bios::load32(uint32_t offset)
{
	uint32_t b0 = data[offset + 0];
	uint32_t b1 = data[offset + 1];
	uint32_t b2 = data[offset + 2];
	uint32_t b3 = data[offset + 3];

	uint32_t complete_word = b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
	return complete_word;
}


#pragma once
#include <cstdint>
class Instruction
{
public:
	Instruction();
	Instruction(uint32_t i);
	~Instruction();

public:
	uint32_t op;

public:
	uint32_t function();
	uint32_t subfunction();
	uint32_t shift();
	uint32_t t();
	uint32_t d();
	uint32_t s();
	uint32_t cop_opcode();


	uint32_t imm();
	uint32_t imm_se();

	uint32_t imm_jump();

};


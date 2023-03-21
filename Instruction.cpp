#include "Instruction.h"

Instruction::Instruction()
{
	op = 0x0;
}
Instruction::Instruction(uint32_t i)
{
	op = i;
}

Instruction::~Instruction()
{
}

uint32_t Instruction::function()
{
	return(op >> 26);
}
uint32_t Instruction::subfunction()
{
	return(op & 0x3F);
}
uint32_t Instruction::shift()
{
	return((op >> 6) & 0x1F);
}

uint32_t Instruction::t()
{
	return((op >> 16) & 0x1F);
}
uint32_t Instruction::s()
{
	return((op >> 21) & 0x1F);
}
uint32_t Instruction::cop_opcode()
{
	return((op >> 21) & 0x1F);
}

uint32_t Instruction::d()
{
	return((op >> 11) & 0x1F);
}

uint32_t Instruction::imm()
{
	return(op & 0xFFFF);
}

uint32_t Instruction::imm_se()
{
	uint16_t v = (op & 0xFFFF);
	return(uint32_t(v));
}

uint32_t Instruction::imm_jump()
{
	return(op & 0x3ffffff);
}


#include "Cpu.h"
#include <bitset>

Cpu::Cpu(Interconnect* inter_)
{
	inter = inter_;
	pc = 0xbfc00000;
	next_pc = pc + 4;

	current_pc = 0;
	sr = 0;

	loadRegister = 0;
	loadValue = 0;

	next_instruction = Instruction(0x0);
	for (int i = 0; i < 32; i++) {
		regs[i] = 0xbeadbeef;
		out_regs[i] = 0xbeadbeef;
	}
	regs[0] = 0;
	out_regs[0] = 0;
}
Cpu::~Cpu(){}


void Cpu::run_next_instruction()
{
	

	Instruction instruction = next_instruction;
	next_instruction = Instruction(load32(pc));

	uint32_t reg = loadRegister;
	uint32_t val = loadValue;
	set_reg(reg, val);

	loadRegister = 0;
	loadValue = 0;

	pc += 4;

	decode_and_execute(instruction);
	for (int i = 0; i < 32; i++)
		regs[i] = out_regs[i];
}
uint32_t Cpu::reg(uint32_t index)
{
	return regs[index];
}
void Cpu::set_reg(uint32_t index, uint32_t value)
{
	/*if (index == 10 or index == 11)
	{
		std::cout << "CHanging of regs 10 or 11: " << index << " to- " << value << std::endl;
		std::cout << "current reg[10]: " << out_regs[10] << " reg[11] " << out_regs[11] << std::endl;

		return;
	}*/
	out_regs[index] = value;
	out_regs[0] = 0;
}

void Cpu::branch(uint32_t offset)
{
	uint32_t offs = offset << 2;
	pc = pc + offs - 4;
}
void Cpu::temp(uint32_t off)
{
	uint32_t bb = 14;
}

void Cpu::decode_and_execute(Instruction instruction)
{
	OPCODE_FIELD op = (OPCODE_FIELD)instruction.function();
	std::cout << "Now instruction: "
		<< std::hex << instruction.op << std::endl;
	switch (op)
	{
	case SPECIAL:	op_spec(instruction);	break;
	case J:			op_j(instruction);		break;
	case JAL:		op_jal(instruction);	break;
	case BNE:		op_bne(instruction);	break;
	case ADDI:		op_addi(instruction);	break;
	case ADDIU:		op_addiu(instruction);	break;
	case ANDI:		op_andi(instruction);	break;
	case ORI:		op_ori(instruction);	break;
	case LUI:		op_lui(instruction);	break;
	case COP0:		op_cop0(instruction);	break;
	case LW:		op_lw(instruction);		break;
	case SB:		op_sb(instruction);		break;
	case SH:		op_sh(instruction);		break;
	case SW:		op_sw(instruction);		break;

	default:
		std::cout << "Sorry unhandled instruction: "
			<< std::hex << instruction.op << std::endl;
		exit(-3);
	}
	
}




void Cpu::op_lui(Instruction instruction)
{
	uint32_t i = instruction.imm();
	uint32_t t = instruction.t();

	uint32_t v = i << 16;
	set_reg(t, v);
}
void Cpu::op_ori(Instruction instruction)
{
	uint32_t i = instruction.imm();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = reg(s) | i;
	set_reg(t, v);
}
void Cpu::op_sw(Instruction instruction)
{
	if ((sr & 0x10000) != 0)
	{
		std::cout << "Ignoring store while cache is isolated." << std::endl;
		return;
	}
	uint32_t i = instruction.imm();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = reg(s) + i;
	uint32_t v = reg(t);

	store32(addr, v);
}
void Cpu::op_addiu(Instruction instruction)
{
	uint32_t i = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = reg(s) + i;
	std::cout << "ADDIU register- " << std::hex << t <<" value = " << std::hex << v
		<< std::endl;

	set_reg(t, v);
}
void Cpu::op_addi(Instruction instruction)
{
	int32_t i = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	//int32_t ss = (int32_t)reg(s);


	int32_t v = reg(s) + i;

	set_reg(t, v);
}
void Cpu::op_j(Instruction instruction)
{
	uint32_t i = instruction.imm_jump();

	pc = (pc & 0xf0000000) | (i << 2);
}
void Cpu::op_bne(Instruction instruction)
{
	uint32_t i = instruction.imm_se();
	uint32_t s = instruction.s();
	uint32_t t = instruction.t();

	/*std::cout << "s = "
		<< s << " |t = "<< t << " | reg(t) = "<<reg(t) <<" | reg(s) = " << reg(s)
		<< std::endl;
		*/

	if (reg(s) != reg(t))
	{
		//branch(i);
		std::cout << "Branch taken";
	}
}
void Cpu::op_lw(Instruction instruction)
{
	/*if ((sr & 0x10000) != 0)
	{
		std::cout << "Ignoring load while cache is isolated." << std::endl;
		return;
	}*/
	uint32_t i = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = reg(s) + i;

	uint32_t v = load32(addr);
	loadRegister = t;
	loadValue = v;
	//set_reg(t, v);
}
void Cpu::op_sh(Instruction instruction)
{
	/*if ((sr & 0x10000) != 0)
	{
		std::cout << "Ignoring store while cache is isolated." << std::endl;
		return;
	}*/
	uint32_t i = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = reg(s) + i;

	uint32_t v = reg(t);
	
	store16(addr, uint16_t(v));
}
void Cpu::op_jal(Instruction instruction)
{
	uint32_t b = pc;
	std::cout << "PC= " << std::hex << b << std::endl << std::endl;
	set_reg(31, b);

	op_j(instruction);
}
void Cpu::op_andi(Instruction instruction)
{
	uint32_t i = instruction.imm();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t v = reg(s) & i;
	set_reg(t, v);
}
void Cpu::op_sb(Instruction instruction)
{
	/*if ((sr & 0x10000) != 0)
	{
		std::cout << "Ignoring store while cache is isolated." << std::endl;
		return;
	}*/
	uint32_t i = instruction.imm_se();
	uint32_t t = instruction.t();
	uint32_t s = instruction.s();

	uint32_t addr = reg(s) + i;

	uint32_t v = reg(t);

	store8(addr, uint8_t(v));
}




void Cpu::op_spec(Instruction instruction)
{
	OPCODE_FIELD_SPECIAL op = (OPCODE_FIELD_SPECIAL)instruction.subfunction();
	switch (op)
	{
	case SLL:	op_sll(instruction);	break;
	case JR:	op_jr(instruction);		break;
	//case 0b001101:
	case OR:	op_or(instruction);		break;
	case SLTU:	op_sltu(instruction);	break;
	case ADDU:	op_addu(instruction);	break;
	//case 0b101011:	
	default:
		std::cout << "Sorry unhandled special instruction: "
			<< std::hex << instruction.op << std::endl;
		exit(-3);
	}
}
void Cpu::op_sll(Instruction instruction)
{
	uint32_t i = instruction.shift();
	uint32_t t = instruction.t();
	uint32_t d = instruction.d();

	uint32_t v = reg(t) << i;

	set_reg(d, v);
}
void Cpu::op_or(Instruction instruction)
{
	uint32_t d = instruction.d();
	uint32_t s = instruction.s();
	uint32_t t = instruction.t();

	uint32_t v = reg(s) | reg(t);

	set_reg(d, v);
}
void Cpu::op_sltu(Instruction instruction)
{
	uint32_t d = instruction.d();
	uint32_t s = instruction.s();
	uint32_t t = instruction.t();

	uint32_t v = reg(s) < reg(t);

	set_reg(d, v);
}
void Cpu::op_addu(Instruction instruction)
{
	uint32_t s = instruction.s();
	uint32_t t = instruction.t();
	uint32_t d = instruction.d();

	uint32_t v = reg(s) + reg(t);

	set_reg(d, v);
}
void Cpu::op_jr(Instruction instruction)
{
	uint32_t s = instruction.s();
	pc = reg(s);
}





void Cpu::op_cop0(Instruction instruction)
{
	uint32_t op = instruction.cop_opcode();
	switch (op)
	{
	case 0b00100:	op_mtc0(instruction);	break;
		//case 0b001111:	
		//case 0b001101:
	//case 0b100101:	op_or(instruction);		break;
	//case 0b101011:	op_sltu(instruction);	break;

	default:
		std::cout << "Sorry unhandled cop0 instruction: "
			<< std::hex << instruction.op << std::endl;
		exit(-3);
	}
}
void Cpu::op_mtc0(Instruction instruction)
{
	uint32_t cpu_r = instruction.t();
	uint32_t cop_r = instruction.d();

	uint32_t v = reg(cpu_r);
	switch (cop_r)
	{
	case 3: case 5:	case 6: case 7:	case 9: case 11:
		if (v != 0)
			std::cout << "Unhandled write to cop0r register: " << std::hex
			<< cop_r << std::endl; 
		break;
	case 12: sr = v; break;
	case 13: 
		if (v != 0)
			std::cout << "Unhandled write to CAUSE register: " << std::endl;
		break;
	default: std::cout << "Unhandled cop0 register: " << std::hex 
						<< cop_r << std::endl; break;
	}
}



//d

uint32_t Cpu::load32(uint32_t addr)
{
		return(inter->load32(pc));
}

void Cpu::store32(uint32_t addr, uint32_t value)
{
		inter->store32(addr, value);
}
void Cpu::store16(uint32_t addr, uint16_t value)
{
		inter->store16(addr, value);
}
void Cpu::store8(uint32_t addr, uint8_t value)
{
		inter->store8(addr, value);
}


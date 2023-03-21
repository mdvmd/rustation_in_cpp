#pragma once
#include <cstdint>
#include "Interconnect.h"
#include "Instruction.h"

class Cpu
{
public:
	Cpu(Interconnect* inter_);
	~Cpu();

public:
	uint32_t pc;
	uint32_t next_pc;
	uint32_t current_pc;
	uint32_t sr;

	Instruction next_instruction;

	uint32_t regs[32];
	uint32_t out_regs[32];


	uint32_t loadRegister;
	uint32_t loadValue;

	Interconnect* inter;

	enum OPCODE_FIELD
	{
		SPECIAL, BcondZ, J, JAL, BEQ, BNE, BLEZ, BGTZ,
		ADDI, ADDIU, SLTI, SLTIU, ANDI, ORI, XORI, LUI,
		COP0, COP1, COP2, COP3, NOP1, NOP2, NOP3, NOP4,
		NOP5, NOP6, NOP7, NOP8, NOP9, NOP10, NOP11, NOP12,
		LB, LH, LWL, LW, LBU, LHU, LWR, NOP13,
		SB, SH, SWL, SW, NOP14, NOP15, SWR, NOP16,
		LWC0, LWC1, LWC2, LWC3, NOP17, NOP18, NOP19, NOP20,
		SWC0, SWC1, SWC2, SWC3, NOP21, NOP22, NOP23, NOP24
	};
	enum OPCODE_FIELD_SPECIAL
	{
		SLL, N_A1, SRL, SRA, SLLV, N_A2, SRLV, SRAV,
		JR, JALR, N_A3, N_A4, SYSCALL, BREAK, N_A5, N_A6,
		MFHI, MTHI, MFLO, MTLO, N_A7, N_A8, N_A9, N_A10,
		MULT, MULTU, DIV, DIVU, N_A11, N_A12, N_A13, N_A14,
		ADD, ADDU, SUB, SUBU, AND, OR, XOR, NOR,
		N_A15, N_A16, SLT, SLTU, N_A17, N_A18, N_A19, N_A20,
		N_A21, N_A22, N_A23, N_A24, N_A25, N_A26, N_A27, N_A28,
		N_A29, N_A30, N_A31, N_A32, N_A33, N_A34, N_A35, N_A36
	};


public:
	void run_next_instruction();
	void decode_and_execute(Instruction instruction);

	uint32_t reg(uint32_t index);
	void  set_reg(uint32_t index, uint32_t value);
	void branch(uint32_t offset);

	void temp(uint32_t off);


	void op_lui(Instruction instruction);
	void op_ori(Instruction instruction);
	void op_sw(Instruction instruction);
	void op_addiu(Instruction instruction);
	void op_addi(Instruction instruction);
	void op_j(Instruction instruction);
	void op_bne(Instruction instruction);
	void op_lw(Instruction instruction);
	void op_sh(Instruction instruction);
	void op_jal(Instruction instruction);
	void op_andi(Instruction instruction);
	void op_sb(Instruction instruction);




	void op_spec(Instruction instruction);
	void op_sll(Instruction instruction);
	void op_or(Instruction instruction);
	void op_sltu(Instruction instruction);
	void op_addu(Instruction instruction);
	void op_jr(Instruction instruction);

	void op_cop0(Instruction instruction);
	void op_mtc0(Instruction instruction);



	uint32_t load32(uint32_t pc);
	void store32(uint32_t addr, uint32_t value);
	void store16(uint32_t addr, uint16_t value);
	void store8(uint32_t addr, uint8_t value);

};


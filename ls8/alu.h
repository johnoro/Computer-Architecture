#ifndef _ALU_H_
#define _ALU_H_

#include "cpu.h"
#include "byte.h"

// ALU operations
enum alu_op {
  ALU_NULL,
	ALU_MUL,
  ALU_ADD,
  ALU_INC,
  ALU_DEC,
  ALU_CMP
	// Add more here
};

enum alu_op get_op(byte instruction);

void alu(struct cpu *cpu, enum alu_op op, byte regA, byte regB);

void handle_alu_op(struct cpu *cpu, byte instruction, byte regA, byte regB);

#endif

#include <stdio.h>
#include <string.h>
#include "alu.h"
#include "cpu.h"
#include "byte.h"

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, byte regA, byte regB) {
  byte result;
  switch (op) {
    case ALU_MUL:
      result = cpu->registers[regA] * cpu->registers[regB];
      break;

    case ALU_ADD:
      result = cpu->registers[regA] + cpu->registers[regB];
      break;

    case ALU_INC:
      result = cpu->registers[regA] + 1;
      break;
    
    case ALU_DEC:
      result = cpu->registers[regA] - 1;
      break;
    
    case ALU_CMP:
      if (cpu->registers[regA] == cpu->registers[regB])
        cpu->fl = 0b00000001;
      else {
        if (cpu->registers[regA] > cpu->registers[regB]) 
          cpu->fl = 0b00000010;
        else
          cpu->fl = 0b00000100;
      }
      return;

    case ALU_NULL:
      printf("An ALU instruction occurred that has not yet been implemented.\n");
      return;
  }

  cpu->registers[regA] = result & 0xFF;
}

enum alu_op get_op(byte instruction) {
  switch (instruction) {
    case MUL:
      return ALU_MUL;
    case ADD:
      return ALU_ADD;
    case INC:
      return ALU_INC;
    case DEC:
      return ALU_DEC;
    case CMP:
      return ALU_CMP;
    default:
      return ALU_NULL;
  }
}

void handle_alu_op(struct cpu *cpu, byte instruction, byte regA, byte regB) {
  enum alu_op op = get_op(instruction);
  alu(cpu, op, regA, regB);
};

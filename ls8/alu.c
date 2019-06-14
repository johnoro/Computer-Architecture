#include <stdio.h>
#include <string.h>
#include "alu.h"
#include "cpu.h"
#include "byte.h"

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, byte opA, byte opB) {
  short int result;
  switch (op) {
    case ALU_CMP:
      if (cpu->registers[opA] == cpu->registers[opB])
        cpu->fl = 0b00000001;
      else {
        if (cpu->registers[opA] > cpu->registers[opB]) 
          cpu->fl = 0b00000010;
        else
          cpu->fl = 0b00000100;
      }
      return;
    
    case ALU_ADD:
      result = cpu->registers[opA] + cpu->registers[opB];
      break;
    
    case ALU_ADDI:
      result = cpu->registers[opA] + opB;
      break;

    case ALU_SUB:
      result = cpu->registers[opA] - cpu->registers[opB];
      break;

    case ALU_INC:
      result = cpu->registers[opA] + 1;
      break;
    
    case ALU_DEC:
      result = cpu->registers[opA] - 1;
      break;
    
    case ALU_MUL:
      result = cpu->registers[opA] * cpu->registers[opB];
      break;
    
    case ALU_DIV:
      result = cpu->registers[opA] / cpu->registers[opB];
      break;
    
    case ALU_MOD:
      result = cpu->registers[opA] % cpu->registers[opB];
      break;
    
    case ALU_NOT:
      result = ~cpu->registers[opA];
      break;
    
    case ALU_AND:
      result = cpu->registers[opA] & cpu->registers[opB];
      break;
    
    case ALU_OR:
      result = cpu->registers[opA] | cpu->registers[opB];
      break;
    
    case ALU_XOR:
      result = cpu->registers[opA] ^ cpu->registers[opB];
      break;
    
    case ALU_SHL:
      result = cpu->registers[opA] << cpu->registers[opB];
      break;
    
    case ALU_SHR:
      result = cpu->registers[opA] >> cpu->registers[opB];
      break;

    case ALU_NULL:
    default:
      printf("\nAn ALU instruction occurred that has not yet been implemented.\n");
      return;
  }

  cpu->registers[opA] = result & 0xFF;
}

enum alu_op get_op(byte instruction) {
  switch (instruction) {
    case CMP:
      return ALU_CMP;
    case ADD:
      return ALU_ADD;
    case ADDI:
      return ALU_ADDI;
    case SUB:
      return ALU_SUB;
    case INC:
      return ALU_INC;
    case DEC:
      return ALU_DEC;
    case MUL:
      return ALU_MUL;
    case DIV:
      return ALU_DIV;
    case MOD:
      return ALU_MOD;
    case NOT:
      return ALU_NOT;
    case AND:
      return ALU_AND;
    case OR:
      return ALU_OR;
    case XOR:
      return ALU_XOR;
    case SHL:
      return ALU_SHL;
    case SHR:
      return ALU_SHR;
    default:
      return ALU_NULL;
  }
}

void handle_alu_op(struct cpu *cpu, byte instruction, byte opA, byte opB) {
  enum alu_op op = get_op(instruction);
  alu(cpu, op, opA, opB);
};

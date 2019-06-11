#include <stdio.h>
#include <string.h>
#include "alu.h"
#include "cpu.h"
#include "byte.h"

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, byte regA, byte regB) {
  switch (op) {
    case ALU_MUL:
      cpu->registers[regA] *= cpu->registers[regB];
      break;

    case ALU_ADD:
      cpu->registers[regA] += cpu->registers[regB];
      break;

    // TODO: implement more ALU ops
    case ALU_NULL:
      printf("An ALU instruction occurred that has not yet been implemented.\n");
      break;
  }
}

enum alu_op get_op(byte instruction) {
  switch (instruction) {
    case MUL:
      return ALU_MUL;
    case ADD:
      return ALU_ADD;
    default:
      return ALU_NULL;
  }
}

void handle_alu_op(struct cpu *cpu, byte instruction, byte regA, byte regB) {
  enum alu_op op = get_op(instruction);
  alu(cpu, op, regA, regB);
};

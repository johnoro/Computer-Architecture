#include <stdio.h>
#include <string.h>
#include "cpu.h"
#include "alu.h"
#include "ram.h"
#include "byte.h"

#define STACK_IND (REGISTERS_LEN-1)

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu) {
  byte instruction, operand1, operand2;
  int running = 1, num_operands, is_alu_op;

  while (running) {
    // 1. Get the value of the current instruction (in address PC).
    cpu->ir = cpu->pc++;
    instruction = ram_read(cpu->ir);

    // 2. Figure out how many operands this next instruction requires
    num_operands = instruction >> 6;
    
    // 3. Get the appropriate value(s) of the operands following this instruction
    if (num_operands > 0) {
      operand1 = ram_read(cpu->pc++);
      if (num_operands > 1)
        operand2 = ram_read(cpu->pc++);
    }
    
    is_alu_op = is_bit_set(instruction, 5);
    if (is_alu_op) {
      handle_alu_op(cpu, instruction, operand1, operand2);
      continue;
    }

    // 4. switch() over it to decide on a course of action.
    switch (instruction) {
      case LDI:
        cpu->registers[operand1] = operand2;
        break;
      
      case PRN:
        printf("%d\n", cpu->registers[operand1]);
        break;
      
      case PRA:
        printf("%c", cpu->registers[operand1]);
        break;
      
      case HLT:
        running = 0;
        break;

      case PUSH:
        ram_write(--cpu->registers[STACK_IND], cpu->registers[operand1]);
        break;

      case POP:
        cpu->registers[operand1] = ram_read(cpu->registers[STACK_IND]++);
        break;

      case CALL:
        ram_write(--cpu->registers[STACK_IND], cpu->pc);
        cpu->pc = cpu->registers[operand1];
        break;
      
      case RET:
        cpu->pc = ram_read(cpu->registers[STACK_IND]++);
        break;
      
      case JMP:
        cpu->pc = cpu->registers[operand1];
        break;

      case JLT:
        if (is_bit_set(cpu->fl, 2))
          cpu->pc = cpu->registers[operand1];
        break;
      
      case JLE:
        if (is_bit_set(cpu->fl, 2) || is_bit_set(cpu->fl, 0))
          cpu->pc = cpu->registers[operand1];
        break;

      default:
        printf("An instruction occurred that has not yet been implemented.\n");
        break;
    }
  }
}

/**
 * Initialize a CPU struct and RAM
 */
void cpu_init(struct cpu *cpu) {
  cpu->pc = 0;
  cpu->ir = 0;
  cpu->mar = 0;
  cpu->mdr = 0;
  cpu->fl = 0;

  memset(cpu->registers, 0, STACK_IND);
  cpu->registers[STACK_IND] = DATA_MAX;
  ram_init();
}

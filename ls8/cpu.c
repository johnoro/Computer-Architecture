#include <stdio.h>
#include <string.h>
#include <time.h>
#include "cpu.h"
#include "alu.h"
#include "ram.h"
#include "byte.h"
#include "interrupt.h"
#include "cpu_helpers.h"

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu) {
  byte instruction, operand1, operand2;
  int running = 1, num_operands, is_alu_op, is_interrupt;
  clock_t start = clock(), end;
  double cpu_time_used;

  while (running) {
    end = clock();
    cpu_time_used = ((double) end - start) / CLOCKS_PER_SEC;
    if (cpu_time_used >= 1) {
      cpu->registers[IS] |= 1;
      start = clock();
    }

    is_interrupt = handle_interrupt(cpu);
    if (is_interrupt) {
      is_interrupt = 0;
      continue;
    }

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

    // printf("\nTRACE: %02X: %02X\n", cpu->pc, cpu->ir);

    // 4. switch() over it to decide on a course of action.
    switch (instruction) {
      case LDI:
        cpu->registers[operand1] = operand2;
        break;
      
      case LD:
        cpu->registers[operand1] = ram_read(cpu->registers[operand2]);
        break;
      
      case ST:
        ram_write(cpu->registers[operand1], cpu->registers[operand2]);
        break;
      
      case INT:
        cpu->registers[IS] |= 1 << cpu->registers[operand1];
        break;
      
      case IRET:
        for (int i = 6; i >= 0; i--)
          cpu->registers[i] = pop(cpu);
        cpu->fl = pop(cpu);
        cpu->pc = pop(cpu);
        cpu->registers[IM] = 255;
        break;
      
      case PRN:
        printf("%d\n", cpu->registers[operand1]);
        break;
      
      case PRA:
        printf("%c", cpu->registers[operand1]);
        fflush(stdout);
        break;
      
      case HLT:
        running = 0;
        break;
      
      case NOP:
        break;

      case PUSH:
        push(cpu, cpu->registers[operand1]);
        break;

      case POP:
        cpu->registers[operand1] = pop(cpu);
        break;

      case CALL:
        push(cpu, cpu->pc);
        jmp(cpu, operand1);
        break;
      
      case RET:
        cpu->pc = pop(cpu);
        break;
      
      case JMP:
        jmp(cpu, operand1);
        break;

      case JLT:
        jmp_if(cpu, operand1, is_bit_set(cpu->fl, 2));
        break;
      
      case JLE:
        jmp_if(cpu, operand1, is_bit_set(cpu->fl, 2) || is_bit_set(cpu->fl, 0));
        break;
      
      case JEQ:
        jmp_if(cpu, operand1, is_bit_set(cpu->fl, 0));
        break;
      
      case JNE:
        jmp_if(cpu, operand1, !is_bit_set(cpu->fl, 0));
        break;
      
      case JGE:
        jmp_if(cpu, operand1, is_bit_set(cpu->fl, 1) || is_bit_set(cpu->fl, 0));
        break;
      
      case JGT:
        jmp_if(cpu, operand1, is_bit_set(cpu->fl, 1));
        break;

      default:
        printf("\nAn instruction occurred that has not yet been implemented.\n");
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

  memset(cpu->registers, 0, SP);
  cpu->registers[SP] = DATA_MAX;
  ram_init();
}

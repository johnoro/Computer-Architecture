#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cpu.h"
#include "alu.h"
#include "byte.h"

#define DATA_MAX RAM_LEN

#define STACK_IND (REGISTERS_LEN-1)

byte cpu_ram_read(struct cpu *cpu, int index) {
  return cpu->ram[index];
}

void cpu_ram_write(struct cpu *cpu, int index, byte value) {
  cpu->ram[index] = value;
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, char *file_name) {
  FILE *fp = fopen(file_name, "r");
  char *line = NULL, *end;
  int data_len = 0, line_len;
  size_t len = 0;
  byte data[DATA_MAX], bits;

  while ((line_len = getline(&line, &len, fp)) != -1) {
    bits = strtoul(line, &end, 2);
    
    if (end != line)
      data[data_len++] = bits;
  }

  memcpy(cpu->ram, data, data_len);

  fclose(fp);
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu) {
  byte instruction, operand1, operand2;
  int running = 1, num_operands, is_alu_op, does_set_pc;

  while (running) {
    // 1. Get the value of the current instruction (in address PC).
    instruction = cpu_ram_read(cpu, cpu->pc);

    does_set_pc = is_bit_set(instruction, 4);
    cpu->ir = does_set_pc ? cpu->pc : cpu->pc++;
    
    // 2. Figure out how many operands this next instruction requires
    num_operands = instruction >> 6;

    // 3. Get the appropriate value(s) of the operands following this instruction
    if (num_operands > 0) {
      operand1 = cpu_ram_read(cpu, cpu->pc++);
      if (num_operands > 1)
        operand2 = cpu_ram_read(cpu, cpu->pc++);
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
      
      case HLT:
        running = 0;
        break;

      case PUSH:
        cpu_ram_write(cpu, --cpu->registers[STACK_IND], cpu->registers[operand1]);
        break;

      case POP:
        cpu->registers[operand1] = cpu_ram_read(cpu, cpu->registers[STACK_IND]++);
        break;

      // TODO:
      // implement more instructions
      
      default:
        printf("An instruction occurred that has not yet been implemented.\n");
        break;
    }
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu) {
  cpu->pc = 0;
  cpu->ir = 0;
  cpu->mar = 0;
  cpu->mdr = 0;
  cpu->fl = 0;

  memset(cpu->registers, 0, STACK_IND);
  cpu->registers[STACK_IND] = 0xF4;
  memset(cpu->ram, 0, RAM_LEN);
}

#include "cpu_helpers.h"
#include "cpu.h"
#include "byte.h"
#include "ram.h"

void push(struct cpu *cpu, byte value) {
  ram_write(--cpu->registers[SP], value);
}

byte pop(struct cpu *cpu) {
  return ram_read(cpu->registers[SP]++);
}

void jmp_if(struct cpu *cpu, byte addr, int cond) {
  if (cond)
    cpu->pc = cpu->registers[addr];
}

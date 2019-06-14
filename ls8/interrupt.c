#include "cpu.h"
#include "cpu_helpers.h"
#include "byte.h"
#include "ram.h"

int handle_interrupt(struct cpu *cpu) {
  byte interrupts = cpu->registers[IS] & cpu->registers[IM];
  int is_interrupt;
  for (int i = 0; i < 8; i++) {
    is_interrupt = is_bit_set(interrupts, i);
    if (is_interrupt) {
      cpu->registers[IM] = 0;

      cpu->registers[IS] ^= 1 << i;
      push(cpu, cpu->pc);
      push(cpu, cpu->fl);
      for (int j = 0; j < 7; j++)
        push(cpu, cpu->registers[j]);
      cpu->pc = ram_read(IV_TABLE + i);

      break;
    }
  }
  return is_interrupt;
}

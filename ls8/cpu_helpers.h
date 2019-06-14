#ifndef _CPU_HELPERS_H_
#define _CPU_HELPERS_H_

#include "cpu.h"
#include "byte.h"
#include "ram.h"

void push(struct cpu *cpu, byte value);
byte pop(struct cpu *cpu);
void jmp_if(struct cpu *cpu, byte addr, int cond);

#endif

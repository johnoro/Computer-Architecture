#ifndef _CPU_H_
#define _CPU_H_

#define REGISTERS_LEN 8
#define RAM_LEN 256

typedef unsigned char byte;

// Holds all information about the CPU
struct cpu {
  // https://github.com/johnoro/Computer-Architecture/blob/master/LS8-spec.md#internal-registers
  int pc;
  byte ir;
  byte mar;
  byte mdr;
  byte fl;

  byte registers[REGISTERS_LEN];
  byte ram[RAM_LEN];
};

// ALU operations
enum alu_op {
	ALU_MUL
	// Add more here
};

// Instructions

// These use binary literals. If these aren't available with your compiler, hex
// literals should be used.
#define LDI 0b10000010
#define PRN 0b01000111
#define HLT 0b00000001
// TODO: more instructions here. These can be used in cpu_run().

// Function declarations
extern void cpu_load(struct cpu *cpu);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif

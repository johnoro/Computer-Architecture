#ifndef _CPU_H_
#define _CPU_H_

#include "byte.h"

#define REGISTERS_LEN 8
#define SP (REGISTERS_LEN-1)
#define IS (REGISTERS_LEN-2)
#define IM (REGISTERS_LEN-3)

// Holds all information about the CPU
struct cpu {
  // https://github.com/johnoro/Computer-Architecture/blob/master/LS8-spec.md#internal-registers
  int pc;
  byte ir;
  byte mar;
  byte mdr;
  byte fl;

  byte registers[REGISTERS_LEN];
};

/* Instructions */
// General CPU
#define LDI 0b10000010
#define LD 0b10000011
#define ST 0b10000100
#define INT 0b01010010
#define IRET 0b00010011
#define PRN 0b01000111
#define PRA 0b01001000
#define PRAR 0b01001001
#define HLT 0b00000001
#define NOP 0b00000000
#define PUSH 0b01000101
#define POP 0b01000110
// Alters PC
#define CALL 0b01010000
#define RET 0b00010001
#define JMP 0b01010100
#define JLT 0b01011000
#define JLE 0b01011001
#define JEQ 0b01010101
#define JNE 0b01010110
#define JGE 0b01011010
#define JGT 0b01010111
// ALU
#define CMP 0b10100111
#define ADD 0b10100000
#define SUB 0b10100001
#define INC 0b01100101
#define DEC 0b01100110
#define MUL 0b10100010
#define DIV 0b10100011
#define MOD 0b10100100
#define NOT 0b01101001
#define AND 0b10101000
#define OR 0b10101010
#define XOR 0b10101011
#define SHL 0b10101100
#define SHR 0b10101101

// Function declarations
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif

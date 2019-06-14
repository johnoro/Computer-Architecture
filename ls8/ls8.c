#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"
#include "ram.h"

/**
 * Main
 */
int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Error: the expected single file path was not provided.\n");
    exit(1);
  }

  struct cpu cpu;

  cpu_init(&cpu);
  ram_load(argv[1]);
  cpu_run(&cpu);

  return 0;
}
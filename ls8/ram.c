#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ram.h"

byte ram[RAM_LEN];

byte ram_read(int index) {
  return ram[index];
}

void ram_write(int index, byte value) {
  ram[index] = value;
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void ram_load(char *file_name) {
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

  memcpy(ram, data, data_len);

  fclose(fp);
}

void ram_init() {
  memset(ram, 0, RAM_LEN);
}

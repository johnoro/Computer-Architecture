#ifndef _RAM_H_
#define _RAM_H_

#include "byte.h"

#define RAM_LEN 256
#define DATA_MAX 0xF4
#define IV_TABLE 0xF8

byte ram_read(int index);
void ram_write(int index, byte value);
void ram_load(char *file_name);
void ram_init();

#endif

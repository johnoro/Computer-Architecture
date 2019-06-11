#include "byte.h"

int is_bit_set(byte b, int n) {
  return b & (1 << n);
}

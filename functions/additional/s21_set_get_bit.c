#include "../../s21_decimal.h"

int s21_getbit(s21_decimal value, int index) {
  int mask = 1u << (index % 32);
  return (value.bits[index / 32] & mask) != 0;
}

void s21_setbit(s21_decimal* value, int index, int bit) {
  int mask = 1u << (index % 32);
  value->bits[index / 32] = bit == 0 ? value->bits[index / 32] & ~mask
                                     : value->bits[index / 32] | mask;
}
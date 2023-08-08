#include "../../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_zero_decimal(dst);
  if (src < 0) {
    s21_setsign(dst, 1);
    src *= -1;
  }
  dst->bits[0] = src;
  return CONVERTATION_OK;
}
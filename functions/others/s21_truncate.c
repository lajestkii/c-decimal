#include "../../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return 1;

  s21_zero_decimal(result);

  int scale = s21_getscale(value);
  for (int i = 0; i < scale; i++) {
    int test = 0;
    s21_div_decimal_10(&value, &test);
  }
  s21_setscale(&value, 0);
  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }
  return 0;
}
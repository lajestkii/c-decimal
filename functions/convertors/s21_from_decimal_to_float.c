#include "../../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  double temp = (double)*dst;
  for (int i = 0; i < 96; i++) {
    temp += s21_getbit(src, i) * pow(2, i);
  }
  temp *= pow(10, -s21_getscale(src));
  if (s21_getsign(src)) temp *= -1;
  *dst = (float)temp;
  return CONVERTATION_OK;
}
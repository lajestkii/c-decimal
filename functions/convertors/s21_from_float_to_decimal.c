#include "../../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal* dst) {
  if (dst == NULL) return CONVERTATION_ERROR;

  if (isnan(src) || isinf(src)) return CONVERTATION_ERROR;

  if (src >= 7.922816251e+29 || src <= -7.922816251e+29)
    return CONVERTATION_ERROR;

  double buf = (double)src;
  int sign = 0;
  s21_zero_decimal(dst);
  if (src < 0) {
    s21_setsign(dst, 1);
    sign = 1;
    src *= -1;
    buf *= -1;
  }
  unsigned int scale = 0;
  while (scale <= 28 && (int)buf / (int)powl(2, 21) == 0) {
    buf *= 10;
    scale++;
  }
  buf = round(buf);

  dst->bits[0] = (int)buf;
  dst->bits[3] = scale * 65536;
  s21_setsign(dst, sign);
  return CONVERTATION_OK;
}
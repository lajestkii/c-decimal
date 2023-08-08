#include "../../s21_decimal.h"

/// @brief переводим число из decimal в int
/// @param src deciaml
/// @param dst указатель на int куда положим значение
/// @return 0 - нет ошибки 1 - ошибка конвертации.
int s21_from_decimal_to_int(s21_decimal src, int* dst) {
  int scale = s21_getscale(src);
  int sign = s21_getsign(src);

  int error = CONVERTATION_OK;
  for (int i = 0; i < scale; i++) {
    s21_div_decimal_10(&src, dst);
  }
  if (src.bits[0] > INT_MAX && sign == 0)
    error = CONVERTATION_ERROR;
  else if (src.bits[0] > 2147483648 && sign == 1)
    error = CONVERTATION_ERROR;
  else if (src.bits[1] != 0 || src.bits[2] != 0)
    error = CONVERTATION_ERROR;
  else {
    *dst = src.bits[0];
    if (sign) *dst *= -1;
  }

  return error;
}
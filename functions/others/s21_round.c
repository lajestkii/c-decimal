#include "../../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return 1;

  s21_zero_decimal(result);
  s21_decimal val = {{1, 0, 0, 0}};
  int last = 0;
  int scale = s21_getscale(value);

  for (int i = 0; i < scale; i++) {
    s21_div_decimal_10(&value, &last);
  }
  s21_setscale(&value, 0);
  if (last >= 5) {
    if (!s21_getsign(value))
      s21_add(value, val, result);
    else {
      s21_setsign(&val, 1);
      s21_add(value, val, result);
    }
  } else {
    s21_copy_decimal(result, value);
  }
  return 0;
}
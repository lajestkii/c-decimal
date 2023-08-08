#include "../../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return 1;

  s21_decimal val = {{1, 0, 0, 0}};
  s21_zero_decimal(result);
  s21_truncate(value, result);
  if (s21_getsign(*result) && !s21_is_equal(value, *result)) {
    s21_sub(*result, val, result);
  }
  return 0;
}
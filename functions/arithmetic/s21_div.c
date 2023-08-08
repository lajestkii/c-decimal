#include "../../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_is_zero_mantiss(value_2)) return ARITHMETIC_DIV_ZERO;

  int err = ARITHEMTIC_OK;

  int sign_1 = s21_getsign(value_1);
  int sign_2 = s21_getsign(value_2);

  s21_setsign(result, sign_1 == sign_2 ? 0 : 1);

  s21_setsign(&value_1, 0);
  s21_setsign(&value_2, 0);

  s21_decimal value_orig = value_2;

  while (!s21_is_greater_or_equal(value_2, value_1) &&
         !s21_getbit(value_2, 95)) {
    s21_shift(&value_2);
  }

  while (s21_is_greater_or_equal(value_2, value_orig) ||
         s21_is_greater_or_equal(value_1, value_orig)) {
    s21_shift(result);

    if (s21_is_greater(value_2, value_1)) {
      s21_setbit(result, 0, 0);
    } else {
      s21_sub(value_1, value_2, &value_1);
      s21_setbit(result, 0, 1);
    }
    s21_unshift(&value_2);
  }

  return err;
}
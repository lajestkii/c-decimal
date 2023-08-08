#include "../../s21_decimal.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
  if (s21_is_zero_mantiss(a) && s21_is_zero_mantiss(b)) {
    return COMPARISON_TRUE;
  }
  int res = COMPARISON_TRUE;
  if (s21_getsign(a) != s21_getsign(b)) {
    res = COMPARISON_FALSE;
  }
  if (s21_getscale(a) != s21_getscale(b)) {
    s21_normalization(&a, &b);
  }
  for (int i = 0; i < 96; i++) {
    if (s21_getbit(a, i) != s21_getbit(b, i)) res = COMPARISON_FALSE;
  }

  return res;
}

int s21_abs_is_equal(s21_decimal a, s21_decimal b) {
  if (s21_is_zero_mantiss(a) && s21_is_zero_mantiss(b)) {
    return COMPARISON_TRUE;
  }
  int res = COMPARISON_TRUE;
  if (s21_getscale(a) != s21_getscale(b)) {
    s21_normalization(&a, &b);
  }
  for (int i = 0; i < 96; i++) {
    if (s21_getbit(a, i) != s21_getbit(b, i)) res = COMPARISON_FALSE;
  }

  return res;
}
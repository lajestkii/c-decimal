#include "../../s21_decimal.h"

int s21_is_greater(s21_decimal a, s21_decimal b) {
  if (s21_is_zero_mantiss(a) && s21_is_zero_mantiss(b)) return COMPARISON_FALSE;
  if (s21_getsign(a) == 1 && s21_getsign(b) == 0) return COMPARISON_FALSE;
  if (s21_getsign(a) == 0 && s21_getsign(b) == 1) return COMPARISON_TRUE;

  int res = COMPARISON_TRUE;
  int sign = s21_getsign(a);
  int flag = 1;
  s21_normalization(&a, &b);
  for (int i = 95; i >= 0 && flag; i--) {
    int bit_a = s21_getbit(a, i);
    int bit_b = s21_getbit(b, i);
    if (bit_a == 1 && bit_b == 0) {
      flag = 0;
      res = COMPARISON_TRUE && !sign;
    } else if (bit_a == 0 && bit_b == 1) {
      flag = 0;
      res = COMPARISON_FALSE || sign;
    }
  }
  return res && !flag;
}
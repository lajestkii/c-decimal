#include "../../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int err = ARITHEMTIC_OK;
  int res_scale = 0;
  int res_sign = 0;
  s21_zero_decimal(result);
  s21_decimal temp = value_1;
  int flag = 0;
  for (int i = 0; i < 95; i++) {
    if (s21_getbit(value_2, i)) {
      if (flag) err++;
      err += s21_add_with_equal_sign(*result, temp, 0, result);
      flag = 0;
    }
    flag = s21_shift(&temp);
  }

  res_scale = s21_getscale(value_1) + s21_getscale(value_2);
  s21_setscale(result, res_scale);

  for (int i = res_scale; i > 28; i--) {
    int sum = 0;
    s21_div_decimal_10(result, &sum);
  }

  res_sign = s21_getsign(value_1) == s21_getsign(value_2) ? 0 : 1;
  s21_setsign(result, res_sign);

  if (err > 0) {
    err = res_sign ? ARITHMETIC_SMALL_NUMBER : ARITHMETIC_LARGE_NUMBER;
    s21_zero_decimal(result);
  } else {
    err = ARITHEMTIC_OK;
  }

  return err;
}

// int main(void) {
//     s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
//     s21_decimal value_2 = {{2, 0, 0, 0}};
//     s21_decimal result = {{0, 0, 0, 0}};
//     s21_decimal check = {{0, 0, 0, 0}};
//     int return_value = s21_mul(value_1, value_2, &result);

//     int test = s21_mul(value_1, value_2, &result);

//     printf("%d", test);
//     s21_print_decimal(result);
//     return 0;
// }
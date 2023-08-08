#include "../../s21_decimal.h"

int s21_add_with_equal_sign(s21_decimal value_1, s21_decimal value_2, int sign,
                            s21_decimal *result) {
  int err = 0;
  int temp = 0;
  for (int i = 0; i < 96; i++) {
    int sum = s21_getbit(value_1, i) + s21_getbit(value_2, i) + temp;
    if (sum == 2) {
      temp = 1;
      sum = 0;
    } else if (sum == 3) {
      sum = 1;
      temp = 1;
    } else {
      temp = 0;
    }
    s21_setbit(result, i, sum);
  }
  if (temp == 1) {
    err = sign ? ARITHMETIC_SMALL_NUMBER : ARITHMETIC_LARGE_NUMBER;
  }
  s21_setsign(result, sign);
  return err;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = ARITHEMTIC_OK;
  s21_zero_decimal(result);

  int sign_1 = s21_getsign(value_1);
  int sign_2 = s21_getsign(value_2);

  err += s21_normalization(&value_1, &value_2);
  s21_setscale(result, s21_getscale(value_1));

  if (sign_1 == sign_2) {
    err += s21_add_with_equal_sign(value_1, value_2, sign_1, result);
  } else {
    if (s21_abs_is_equal(value_1, value_2)) {
      s21_zero_decimal(result);
    } else if (s21_is_less(value_1, value_2)) {
      s21_setsign(&value_1, 0);
      if (s21_is_less(value_1, value_2)) {
        err += s21_sub(value_2, value_1, result);
        s21_setsign(result, 0);
      } else {
        err += s21_sub(value_1, value_2, result);
        s21_setsign(result, 1);
      }
    } else {
      s21_setsign(&value_2, 0);
      if (s21_is_less(value_1, value_2)) {
        err += s21_sub(value_2, value_1, result);
        s21_setsign(result, 1);
      } else {
        err += s21_sub(value_1, value_2, result);
        s21_setsign(result, 0);
      }
    }
  }
  if (err > 0) {
    if (s21_getsign(*result)) {
      err = ARITHMETIC_SMALL_NUMBER;
    } else {
      err = ARITHMETIC_LARGE_NUMBER;
    }
  }
  return err;
}

// int main(void) {
//   s21_decimal dec1 = {{0}};
//   s21_decimal dec2 = {{0}};
//   dec1.bits[3] = 0x300000;
//   dec1.bits[2] = 0;
//   dec1.bits[1] = 0xF;
//   dec1.bits[0] = 0x67E4FEEF;
//   dec2.bits[3] = 0x300000;
//   dec2.bits[2] = 0;
//   dec2.bits[1] = 0xFF;
//   dec2.bits[0] = 0x67E4FFFF;
//   s21_decimal res = {{0}};
//   res.bits[3] = 0x300000;
//   res.bits[2] = 0;
//   res.bits[1] = 0x10E;
//   res.bits[0] = 0xCFC9FEEE;
//   s21_decimal res1 = {{0}};
//   s21_add(dec1, dec2, &res1);
//   s21_print_decimal(res);
// }

// //00000000001100000000000000000000 | 00000000000000000000000000000000 |
// 00000000000000000000000100001110 | 11001111110010011111111011101110

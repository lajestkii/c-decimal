#include "../../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = ARITHEMTIC_OK;
  int sign_1 = s21_getsign(value_1);
  int sign_2 = s21_getsign(value_2);
  s21_zero_decimal(result);

  int is_less = s21_is_less(value_1, value_2);

  err += s21_normalization(&value_1, &value_2);
  err += s21_setscale(result, s21_getscale(value_1));

  if (sign_1 == sign_2) {
    if (is_less && !sign_1) {
      mantis_subtraction(value_2, value_1, result);
      s21_setsign(result, 1);
    } else if (is_less && sign_1) {
      mantis_subtraction(value_1, value_2, result);
      s21_setsign(result, 1);
    } else if (!is_less && sign_1) {
      mantis_subtraction(value_2, value_1, result);
      s21_setsign(result, 0);
    } else {
      mantis_subtraction(value_1, value_2, result);
      s21_setsign(result, 0);
    }
  } else {
    err += mantis_addition(value_1, value_2, result, 1);
    s21_setsign(result, sign_1);
  }

  // -400 - 500 = -900

  if (err > 0) {
    if (s21_getsign(*result))
      err = ARITHMETIC_SMALL_NUMBER;
    else
      err = ARITHMETIC_LARGE_NUMBER;
  }

  return err;
}
// 400 - 500

int mantis_addition(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result, int sign) {
  int err = ARITHEMTIC_OK;
  int val_1 = 0, val_2 = 0, res = 0, ost = 0;
  for (int i = 0; i < 96; ++i) {
    val_1 = s21_getbit(value_1, i);
    val_2 = s21_getbit(value_2, i);
    res = val_1 + val_2 + ost;
    s21_setbit(result, i, res % 2);
    ost = (res > 1) ? 1 : 0;
  }
  if (ost) err = sign ? ARITHMETIC_SMALL_NUMBER : ARITHMETIC_LARGE_NUMBER;

  return err;
}

void mantis_subtraction(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal *result) {
  int bit_1 = 0, bit_2 = 0, bit_result = 0;
  for (int i = 0; i < 96; ++i) {
    bit_1 = s21_getbit(value_1, i);
    bit_2 = s21_getbit(value_2, i);
    if (bit_1 < bit_2) {
      bit_1 += 2;
      conversion(&value_1, i);
    }
    bit_result = bit_1 - bit_2;
    s21_setbit(result, i, bit_result);
  }
}

void conversion(s21_decimal *dec, int i) {
  int bit = 0;
  for (; !bit && i < 96; ++i) {
    bit = s21_getbit(*dec, i);
    s21_setbit(dec, i, !bit);
  }
}

// int main(void) {
//     s21_decimal src1, src2;
//     src1.bits[0] = 0b10000010111000100101101011101101;
//     src1.bits[1] = 0b11111001111010000010010110101101;
//     src1.bits[2] = 0b10110000001111101111000010010100;
//     src1.bits[3] = 0b10000000000011100000000000000000;

//     // -5.352654545456454545645464 exp 24
//     src2.bits[0] = 0b01001000000110110001111110011000;
//     src2.bits[1] = 0b11111011111111011000100101101101;
//     src2.bits[2] = 0b00000000000001000110110101110111;
//     src2.bits[3] = 0b10000000000110000000000000000000;
//     s21_decimal result = {{0, 0, 0, 0}};
//     // -54545451245453999999999999999 exp 14
//     s21_sub(src1, src2, &result);

//     // -54545451245453999999999999999 exp 14
//     s21_print_decimal(result);

// }

/*

*/

// int main ()
// {
//       s21_decimal src1, src2, origin, result;
//   // src1 = 0.5456465465486476846545465485;
//   // src2 = 0.68985125146545154;
//   src1.bits[0] = 0b00001011000011110111000010001101;
//   src1.bits[1] = 0b10010110101100000101100101010001;
//   src1.bits[2] = 0b00010001101000010111101110000001;
//   src1.bits[3] = 0b00000000000111000000000000000000;
//   src2.bits[0] = 0b00010111001001010100110000000010;
//   src2.bits[1] = 0b00000000111101010001010110011011;
//   src2.bits[2] = 0b00000000000000000000000000000000;
//   src2.bits[3] = 0b00000000000100010000000000000000;

//   origin.bits[0] = 0b01011010101111100101111101110011;
//   origin.bits[1] = 0b00101101001111010011000001101000;
//   origin.bits[2] = 0b00000100101010001101010101010111;
//   origin.bits[3] = 0b10000000000111000000000000000000;

//     s21_print_decimal(src1);
//     s21_print_decimal(src2);
//     s21_sub(src1, src2, &result);
//     printf("result\n");
//     s21_print_decimal(result);
//     printf("answer\n");
//     s21_print_decimal(origin);

//     return 0;
// }
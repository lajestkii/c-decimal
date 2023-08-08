#include "../../s21_decimal.h"

void s21_div_decimal_10(s21_decimal* dec, int* res) {
  uint64_t a = 0;
  *res = 0;
  for (int i = 2; i >= 0; i--) {
    a = *res * 4294967296 + dec->bits[i];
    dec->bits[i] = a / 10;
    *res = a - 10 * dec->bits[i];
  }
}

int s21_is_zero_mantiss(s21_decimal dec) {
  return !dec.bits[0] && !dec.bits[1] && !dec.bits[2];
}

int s21_shift(s21_decimal* dec) {
  int val_1 = 0;
  int val_2 = 0;
  int err = s21_getbit(*dec, 95);
  for (int i = 0; i < 96; i++) {
    val_1 = s21_getbit(*dec, i);
    s21_setbit(dec, i, val_2);
    val_2 = val_1;
  }
  return err;
}

void s21_unshift(s21_decimal* dec) {
  int val_1 = 0;
  int val_2 = 0;
  for (int i = 95; i >= 0; i--) {
    val_1 = s21_getbit(*dec, i);
    s21_setbit(dec, i, val_2);
    val_2 = val_1;
  }
}

/// @brief умножение на 10
/// @return возвращает 1 при переполнении, 0 если все ок

int s21_mult_decimal_10(s21_decimal* dec) {
  int err = 0;
  s21_decimal temp_dec = *dec;
  s21_decimal temp_dec1 = *dec;

  s21_zero_mantiss(dec);

  for (int i = 0; i < 3; i++) err += s21_shift(&temp_dec);

  err += s21_shift(&temp_dec1);

  err += s21_add_with_equal_sign(temp_dec, temp_dec1, s21_getsign(*dec), dec);
  return err > 0 ? 1 : 0;
}

void s21_zero_decimal(s21_decimal* val) {
  val->bits[0] = 0;
  val->bits[1] = 0;
  val->bits[2] = 0;
  val->bits[3] = 0;
}

void s21_zero_mantiss(s21_decimal* val) {
  val->bits[0] = 0;
  val->bits[1] = 0;
  val->bits[2] = 0;
}

void s21_print_decimal(s21_decimal dec) {
  printf("sign: %s\n", !s21_getsign(dec) ? "positive" : "negative");
  for (int i = 0; i <= 3; i++) {
    printf("dec: %d --- %u\n", i, dec.bits[i]);
  }
  printf("scale: %d\n", s21_getscale(dec));
}

void s21_copy_decimal(s21_decimal* dst, s21_decimal src) {
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[3] = src.bits[3];
}
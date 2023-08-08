#include "../../s21_decimal.h"

int s21_normalization(s21_decimal* a, s21_decimal* b) {
  int err = 0;

  int scale_a = s21_getscale(*a);
  int scale_b = s21_getscale(*b);

  int scale_result = scale_a > scale_b ? scale_a : scale_b;

  int bigger = scale_a > scale_b ? 1 : 0;
  int diff = bigger ? scale_a - scale_b : scale_b - scale_a;

  s21_decimal temp_a = {{a->bits[0], a->bits[1], a->bits[2], a->bits[3]}};
  s21_decimal temp_b = {{b->bits[0], b->bits[1], b->bits[2], b->bits[3]}};

  for (int i = 0; i < diff; i++) {
    if (bigger) {
      err += s21_mult_decimal_10(&temp_b);
    } else {
      err += s21_mult_decimal_10(&temp_a);
    }
  }
  if (err == 0 || scale_result > 28) {
    s21_copy_decimal(a, temp_a);
    s21_copy_decimal(b, temp_b);
    if (bigger)
      s21_setscale(b, scale_a);
    else
      s21_setscale(a, scale_b);
  } else {
    for (int i = 0; i < diff; i++) {
      int sum = 0;
      if (bigger)
        s21_div_decimal_10(a, &sum);
      else
        s21_div_decimal_10(b, &sum);
    }
    if (bigger)
      s21_setscale(a, scale_b);
    else
      s21_setscale(b, scale_a);
  }
  return 0;
}

// /10^5 - /10^5
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum arithmetic_error_code {
  ARITHEMTIC_OK,
  ARITHMETIC_LARGE_NUMBER,
  ARITHMETIC_SMALL_NUMBER,
  ARITHMETIC_DIV_ZERO
};

enum comparison_return_value { COMPARISON_FALSE, COMPARISON_TRUE };

enum convertation_return_value { CONVERTATION_OK, CONVERTATION_ERROR };

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// check
int s21_is_zero_mantiss(s21_decimal dec);
int s21_is_zero(s21_decimal dec);

// additional
int s21_getbit(s21_decimal value, int index);
void s21_setbit(s21_decimal* value, int index, int bit);

int s21_shift(s21_decimal* dec);
void s21_unshift(s21_decimal* dec);

int s21_igetbit(unsigned int value, int index);
void s21_isetbit(unsigned int* value, int index, int bit);

int s21_getsign(s21_decimal val);
void s21_setsign(s21_decimal* val, int sign);

int s21_setscale(s21_decimal* src, int scale);
int s21_getscale(s21_decimal src);

void s21_zero_decimal(s21_decimal* val);
void s21_zero_mantiss(s21_decimal* val);

void s21_print_decimal(s21_decimal dec);
void s21_copy_decimal(s21_decimal* dst, s21_decimal src);

// convertors
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);

// additional arithmetical

int s21_normalization(s21_decimal* a, s21_decimal* b);
int s21_add_with_equal_sign(s21_decimal value_1, s21_decimal value_2, int sign,
                            s21_decimal* result);
void s21_div_decimal_10(s21_decimal* dec, int* res);
int s21_mult_decimal_10(s21_decimal* dec);

int mantis_addition(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal* result, int sing);
void mantis_subtraction(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal* result);
void conversion(s21_decimal* dec, int i);

// arithmetic
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

// additional comparison
int s21_abs_is_equal(s21_decimal a, s21_decimal b);

// comparison
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);

int s21_is_not_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);

// others
int s21_negate(s21_decimal value, s21_decimal* result);
int s21_truncate(s21_decimal value, s21_decimal* result);
int s21_round(s21_decimal value, s21_decimal* result);
int s21_floor(s21_decimal value, s21_decimal* result);
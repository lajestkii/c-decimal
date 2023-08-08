#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "../s21_decimal.h"

#ifndef S21_DECIMAL_TEST_H
#define S21_DECIMAL_TEST_H

Suite *s21_from_decimal_to_int_suite(void);
Suite *suite_from_decimal_to_int(void);
Suite *s21_is_equal_suite(void);
Suite *suite_is_less(void);
Suite *suite_is_greater(void);
Suite *suite_is_greater_or_equal(void);
Suite *s21_suite_is_less_or_equal(void);
Suite *suite_from_int_to_decimal(void);
Suite *suite_from_decimal_to_float(void);
Suite *suite_float_to_decimal(void);
Suite *suite_add(void);
Suite *suite_sub(void);
Suite *suite_negate(void);
Suite *suite_truncate(void);
Suite *suite_mul(void);
Suite *suite_floor(void);
Suite *suite_round(void);
Suite *suite_round2(void);
Suite *suite_truncate2(void);
Suite *suite_div(void);
Suite *suite_is_not_equal(void);

void s21_test_one_suite(Suite *current_suit, int *sum_of_errors);

#endif
#include "s21_decimal_test.h"

START_TEST(from_decimal_to_float_0) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_setscale(&val, 5);
  float res = 1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_float_1) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_setbit(&val, 127, 1);
  s21_setscale(&val, 5);
  float res = -1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_decimal_to_float_2) {
  s21_decimal var = {{0, 0, 0, 0}};
  float value = 0;
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(0.0, value, 10e-5);
}
END_TEST

START_TEST(s21_from_decimal_to_float_1) {
  s21_decimal var = {0};
  float value = 0;
  s21_from_decimal_to_float(var, &value);
  ck_assert_float_eq_tol(0.0, value, 10e-5);
}
END_TEST

START_TEST(s21_from_decimal_to_float_4) {
  s21_decimal value = {{1812, 0, 0, 0}};
  s21_setsign(&value, 1);
  float result = 0;
  float check = -1812;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_5) {
  s21_decimal value = {{18122, 0, 0, 0}};
  s21_setscale(&value, 3);
  s21_setsign(&value, 1);
  float result = 0;
  float check = -18.122;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_6) {
  s21_decimal value = {{0xFFFFFF, 0, 0, 0}};
  float result = 0;
  float check = 16777215;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_7) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  float result = 0;
  float check = 0xFFFFFFFFFFFFFFFF;
  int return_value = s21_from_decimal_to_float(value, &result);
  ck_assert_float_eq(result, check);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_8) {
  s21_decimal src = {0};
  int result = 0;
  float number = 0.0;
  src.bits[0] = 23450987;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 2147745792;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -2345.0987);
  ck_assert_int_eq(result, 0);
}
END_TEST

Suite *suite_from_decimal_to_float(void) {
  Suite *s = suite_create("from_decimal_to_float");
  TCase *tc = tcase_create("from_decimal_to_float_tc");

  tcase_add_test(tc, from_decimal_to_float_0);
  tcase_add_test(tc, from_decimal_to_float_1);
  tcase_add_test(tc, from_decimal_to_float_2);
  tcase_add_test(tc, s21_from_decimal_to_float_1);
  tcase_add_test(tc, s21_from_decimal_to_float_4);
  tcase_add_test(tc, s21_from_decimal_to_float_5);
  tcase_add_test(tc, s21_from_decimal_to_float_6);
  tcase_add_test(tc, s21_from_decimal_to_float_7);
  tcase_add_test(tc, s21_from_decimal_to_float_8);

  suite_add_tcase(s, tc);
  return s;
}
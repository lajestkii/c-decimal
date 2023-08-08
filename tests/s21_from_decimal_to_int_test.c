#include "s21_decimal_test.h"

START_TEST(s21_from_decimal_to_int_1) {
  s21_decimal dec = {{100, 0, 0, 0b00000000000000100000000000000000}};
  int res = 1;
  int check = 0;
  s21_from_decimal_to_int(dec, &check);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_from_decimal_to_int_2) {
  s21_decimal dec = {{0b1, 0b1, 0b0, 0b00000000000001110000000000000000}};
  int res = 429;
  int check = 0;
  s21_from_decimal_to_int(dec, &check);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_from_decimal_to_int_3) {
  s21_decimal dec = {
      {0b11110111, 0b0, 0b0, 0b10000000000000010000000000000000}};
  int res = -24;
  int check = 0;
  s21_from_decimal_to_int(dec, &check);
  ck_assert_int_eq(check, res);
}
END_TEST

START_TEST(s21_from_decimal_to_int_4) {
  s21_decimal dec = {{0b1011, 0b0, 0b0, 0b10000000000000000000000000000000}};
  int res = -11;
  int check = 0;
  s21_from_decimal_to_int(dec, &check);
  ck_assert_int_eq(check, res);
}
END_TEST

Suite *s21_from_decimal_to_int_suite(void) {
  Suite *s;

  TCase *s21_from_decimal_to_int_test;

  s = suite_create("s21_from_decimal_to_int_test");

  s21_from_decimal_to_int_test = tcase_create("s21_from_decimal_to_int_test");

  tcase_add_test(s21_from_decimal_to_int_test, s21_from_decimal_to_int_1);
  tcase_add_test(s21_from_decimal_to_int_test, s21_from_decimal_to_int_2);
  tcase_add_test(s21_from_decimal_to_int_test, s21_from_decimal_to_int_3);
  tcase_add_test(s21_from_decimal_to_int_test, s21_from_decimal_to_int_4);

  suite_add_tcase(s, s21_from_decimal_to_int_test);
  return s;
}
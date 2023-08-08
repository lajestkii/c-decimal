#include "s21_decimal_test.h"

int main(void) {
  int number_failed = 0;
  Suite* s[] = {s21_from_decimal_to_int_suite(),
                s21_is_equal_suite(),
                suite_is_less(),
                suite_is_greater(),
                suite_is_greater_or_equal(),
                s21_suite_is_less_or_equal(),
                suite_from_decimal_to_int(),
                suite_from_int_to_decimal(),
                suite_from_decimal_to_float(),
                suite_add(),
                suite_float_to_decimal(),
                suite_sub(),
                suite_negate(),
                suite_truncate(),
                suite_mul(),
                suite_floor(),
                suite_round(),
                suite_round2(),
                suite_truncate2(),
                suite_div(),
                suite_is_not_equal(),
                NULL};
  for (Suite** current_suit = s; *current_suit != NULL; current_suit++) {
    s21_test_one_suite(*current_suit, &number_failed);
  }
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void s21_test_one_suite(Suite* current_suit, int* sum_of_errors) {
  SRunner* sr;
  sr = srunner_create(current_suit);

  srunner_run_all(sr, CK_NORMAL);
  *sum_of_errors += srunner_ntests_failed(sr);
  srunner_free(sr);
}
#include "../../s21_decimal.h"
/// @brief берем значение бита отвечающий за знак(0 - положительный, 1 -
/// отрицательный)
/// @param val сам децимал в котором берем знак
int s21_getsign(s21_decimal val) { return (val.bits[3] & 1u << 31) != 0; }

/// @brief меняем бит отвечающий за знак
/// @param val сам децимал в котором меняем знак
/// @param sign 0 - положительное число, 1 - отрицательное
void s21_setsign(s21_decimal* val, int sign) { s21_setbit(val, 127, sign); }
#include "../../s21_decimal.h"

int s21_getscale(s21_decimal src) {
  int mask = 255 << 16;
  return (src.bits[3] & mask) >> 16;
}

/// @brief меняем биты отвечающие за степень 10-ки
/// @return 1 - ошибка степень привышает возможную 0 - ок
int s21_setscale(s21_decimal* src, int scale) {
  if (scale > 28) return 1;
  int sign = s21_getsign(*src);
  src->bits[3] = src->bits[3] & (0b00000000 << 16);
  src->bits[3] = (src->bits[3] | ((scale % 28) << 16));
  s21_setsign(src, sign);
  return 0;
}

// TEST

// int main(void) {
//     s21_decimal dec = {{0, 0, 0, 0b10000000000000110000000000000000}}; // 48

//    int previous_sign = s21_getsign(dec);
//    int previous_scale = s21_getscale(dec);

//    s21_setscale(&dec, 11);

//    int new_sign = s21_getsign(dec);
//    int new_scale = s21_getscale(dec);

//    printf("%d - sign : %d - scale\n", previous_sign, previous_scale);
//    printf("%d - sign : %d - scale", new_sign, new_scale);
// }

// 00000000|00000000|00000000|00000000
// знак              всегда нули
// 00000000001100000000000000000000
//             1011

// 11111111|11111111
//            111111

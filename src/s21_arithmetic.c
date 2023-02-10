#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {  // В работе
  int qwert = 138;
  int trewq = 0;
  int position_0 = 0;
  int position_1 = 0;
  int position_2 = 0;
  int check_0 = 0;
  int check_1 = 0;
  int check_2 = 0;
  int check_3 = 0;

  for (; position_0 < 32; position_0++) {
    printf("%d - iteration\n", position_0);
    if (((value_1.bits[0] >> position_0) & 1) == 1) {  // 1 - 0
      if (((value_2.bits[0] >> position_0) & 1) == 0) {
        inversion_bit(&result->bits[0], position_0);
      }
    } else {
      if (((value_2.bits[0] >> position_0) & 1) == 1) {  // 0 - 1
        inversion_bit(&result->bits[0], position_0);
        int i = position_0 + 1;
        for (; i < 32; ++i) {
          if (((value_1.bits[0] >> i) & 1) == 1) {
            inversion_bit(&value_1.bits[0], i);
            check_0 = 1;
            break;
          }
        }
        if (check_0) {
          int k = i - 1;
          for (; k > position_0; k--) {
            inversion_bit(&value_1.bits[0], k);
          }
          check_0 = 0;
        } else {
          int pos_1 = 0;
          for (; pos_1 < 32; pos_1++) {
            if (((value_1.bits[1] >> pos_1) & 1) == 1) {
              inversion_bit(&value_1.bits[1], pos_1);
              check_1 = 1;
              break;
            }
          }
          if (check_1) {
            int l = pos_1 - 1;
            for (; l >= 0; l--) {
              inversion_bit(&value_1.bits[1], l);
            }
            int k = i - 1;
            for (; k > position_0; k--) {
              inversion_bit(&value_1.bits[0], k);
            }
            check_1 = 0;
          }
        }
      }
    }
    print_bits(value_1, value_2, *result);
    print_iteration(qwert, &trewq);
  }
  trewq += 11;
  for (; position_1 < 32; position_1++) {
    printf("%d - iteration\n", position_1);
    if (((value_1.bits[1] >> position_1) & 1) == 1) {  // 1 - 0
      if (((value_2.bits[1] >> position_1) & 1) == 0) {
        inversion_bit(&result->bits[1], position_1);
      }
    } else {
      if (((value_2.bits[1] >> position_1) & 1) == 1) {  // 0 - 1
        inversion_bit(&result->bits[1], position_1);
        int z = position_1 + 1;
        for (; z < 32; ++z) {
          if (((value_1.bits[1] >> z) & 1) == 1) {
            inversion_bit(&value_1.bits[1], z);
            check_2 = 1;
            break;
          }
        }
        if (check_2) {
          int k = z - 1;
          for (; k > position_1; k--) {
            inversion_bit(&value_1.bits[1], k);
          }
          check_2 = 0;
        } else {
          int pos_2 = 0;
          for (; pos_2 < 32; pos_2++) {
            if (((value_1.bits[2] >> pos_2) & 1) == 1) {
              inversion_bit(&value_1.bits[2], pos_2);
              check_3 = 1;
              break;
            }
          }
          if (check_3) {
            int m = pos_2 - 1;
            for (; m >= 0; m--) {
              inversion_bit(&value_1.bits[2], m);
            }
            int k = z - 1;
            for (; k > position_0; k--) {
              inversion_bit(&value_1.bits[1], k);
            }
            check_3 = 0;
          }
        }
      }
    }
    print_bits(value_1, value_2, *result);
    print_iteration(qwert, &trewq);
  }
  return 0;
}

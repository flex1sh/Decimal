//
// Created by root on 2/8/23.
//
#include "stdio.h"
#include "string.h"

typedef struct {
  int bits[4];
} s21_decimal;

void binary_representation(int num);

void int_to_binary_array();

void inversion_bit(int *result, int position);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

void test_decimal_sub();

int main() {
  test_decimal_sub();
  return 0;
}

void binary_representation(int num) {
  for (int j = sizeof(num) * 8 - 1; j >= 0; j--) {
    printf("%d", (num >> j) & 1);
  }
}

void inversion_bit(int *result, int position) {
  int mask = 1 << position;
  *result = *result ^ mask;
}

void int_to_binary_array() {
  int a = 459123;
  int size = 31;
  char aboba[size];
  memset(aboba, '0', size);
  while (a > 0) {
    if ((a % 2) == 1) {
      aboba[size] = '1';
    }
    a = a / 2;
    size -= 1;
  }
  printf("%s\n", aboba);
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {  // В работе
  int qwert = 138;
  int trewq = 0;
  int position_0 = 0;
  int position_1 = 0;
  int position_2 = 0;
  int check_0 = 0;
  int check_1 = 0;
  int check_2 = 0;
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

    printf("value_1 - ");
    for (int i = 2; i >= 0; i--) {
      printf("bits[%d] = ", i);
      binary_representation(value_1.bits[i]);
      printf(" ");
    }
    printf("\n");
    printf("-\n");
    printf("value_2 - ");
    for (int i = 2; i >= 0; i--) {
      printf("bits[%d] = ", i);
      binary_representation(value_2.bits[i]);
      printf(" ");
    }
    printf("\n");
    printf("result -  ");
    for (int i = 2; i >= 0; i--) {
      printf("bits[%d] = ", i);
      binary_representation(result->bits[i]);
      printf(" ");
    }
    printf("\n");

    for (int i = 0; i < qwert - trewq - 1; i++) {
      printf("-");
    }
    printf("^");
    for (int i = trewq; i > 0; i--) {
      printf("-");
    }
    trewq += 1;
    printf("\n");
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
        int i = position_1 + 1;
        for (; i < 32; ++i) {
          if (((value_1.bits[1] >> i) & 1) == 1) {
            inversion_bit(&value_1.bits[1], i);
            check_2 = 1;
            break;
          }
        }
        if (check_2) {
          int k = i - 1;
          for (; k > position_1; k--) {
            inversion_bit(&value_1.bits[1], k);
          }
          check_2 = 0;
        }
        //        else {
        //          int pos_1 = 0;
        //          for (; pos_1 < 32; pos_1++) {
        //            if (((value_1.bits[1] >> pos_1) & 1) == 1) {
        //              inversion_bit(&value_1.bits[1], pos_1);
        //              check_1 = 1;
        //              break;
        //            }
        //          }
        //          if (check_1) {
        //            int l = pos_1 - 1;
        //            for (; l >= 0; l--) {
        //              inversion_bit(&value_1.bits[1], l);
        //            }
        //            int k = i - 1;
        //            for (; k > position_0; k--) {
        //              inversion_bit(&value_1.bits[0], k);
        //            }
        //            check_1 = 0;
        //          }
      }
    }
    printf("value_1 - ");
    for (int i = 2; i >= 0; i--) {
      printf("bits[%d] = ", i);
      binary_representation(value_1.bits[i]);
      printf(" ");
    }
    printf("\n");
    printf("-\n");
    printf("value_2 - ");
    for (int i = 2; i >= 0; i--) {
      printf("bits[%d] = ", i);
      binary_representation(value_2.bits[i]);
      printf(" ");
    }
    printf("\n");
    printf("result -  ");
    for (int i = 2; i >= 0; i--) {
      printf("bits[%d] = ", i);
      binary_representation(result->bits[i]);
      printf(" ");
    }
    printf("\n");

    for (int i = 0; i < qwert - trewq - 1; i++) {
      printf("-");
    }
    printf("^");
    for (int i = trewq; i > 0; i--) {
      printf("-");
    }
    trewq += 1;
    printf("\n");
  }
  return 0;
}

void test_decimal_sub() {
  s21_decimal value_1;
  s21_decimal value_2;
  s21_decimal result;

  value_1.bits[0] = 9;
  value_1.bits[1] = 1024;
  value_1.bits[2] = 12489;
  value_1.bits[3] = 0;

  value_2.bits[0] = 15;
  value_2.bits[1] = 256;
  value_2.bits[2] = 6571;
  value_2.bits[3] = 0;

  result.bits[0] = 0;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0;

  s21_sub(value_1, value_2, &result);

  //  printf("result -  ");
  //  for (int i = 2; i >= 0; i--) {
  //    printf("bits[%d] = ", i);
  //    binary_representation(result.bits[i]);
  //    printf(" ");
  //  }
  printf("\n");
}

//101111111111111111111111111111111111111010
//101111111111111111111111111111111111111010
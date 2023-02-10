#include "s21_decimal.h"

void print_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal result) {
  printf("value_1 - ");
  for (int i = 2; i >= 0; i--) {
    printf("bits[%d] = ", i);
    binary_representation(value_1.bits[i]);
    printf(" ");
  }
  printf("\n");
  // printf("-\n");
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
    binary_representation(result.bits[i]);
    printf(" ");
  }
  printf("\n");
}

void print_iteration(int qwert, int *trewq) {
  for (int i = 0; i < qwert - *trewq - 1; i++) {
    printf("-");
  }
  printf("^");
  for (int i = *trewq; i > 0; i--) {
    printf("-");
  }
  *trewq += 1;
  printf("\n");
}

void test_decimal_sub() {
  s21_decimal value_1;
  s21_decimal value_2;
  s21_decimal result;

  value_1.bits[0] = 5678;  // 1011000101110
  value_1.bits[1] = 1024;  // 10000000000
  value_1.bits[2] = 12489;
  value_1.bits[3] = 0;

  value_2.bits[0] = 493;  // 111101101
  value_2.bits[1] = 999;  // 1111100111
  value_2.bits[2] = 7931;
  value_2.bits[3] = 0;

  result.bits[0] = 0;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0;

  s21_sub(value_1, value_2, &result);

  printf("\n");
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

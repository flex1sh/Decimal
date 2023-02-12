#include "s21_decimal.h"

void print_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal result) {
  printf("value_1 - ");
  for (int i = 3; i >= 0; i--) {
    printf("bits[%d] = ", i);
    binary_representation(value_1.bits[i]);
    printf(" ");
  }
  printf("\n");
  printf("value_2 - ");
  for (int i = 3; i >= 0; i--) {
    printf("bits[%d] = ", i);
    binary_representation(value_2.bits[i]);
    printf(" ");
  }
  printf("\n");
  printf("result -  ");
  for (int i = 3; i >= 0; i--) {
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

  // 110000110010010000000000000000000000000000000000000000000000000000000011111111 - 230381386736558590132479
  value_1.bits[0] = 255;
  value_1.bits[1] = 0;
  value_1.bits[2] = 12489;
  value_1.bits[3] = 196608;  // 3

  // 11110111110110000000000000000000000111110011100000000000000000000000111101101 - 146301127252881126195693
  value_2.bits[0] = 493;
  value_2.bits[1] = 999;
  value_2.bits[2] = 7931;
  value_2.bits[3] = 196608;  // 3

  result.bits[0] = 0;
  result.bits[1] = 0;
  result.bits[2] = 0;
  result.bits[3] = 0;

  s21_sub(value_1, value_2, &result);

  printf("\n");
}

// Выводит целое число в двоичном виде
void binary_representation(int num) {
  for (int j = sizeof(num) * 8 - 1; j >= 0; j--) {
    int bit = (num >> j) & 1;
    if (bit) {
      printf("\033[31m%d\033[0m", bit);
    } else {
      printf("%d", bit);
    }
  }
}

// Инвертирует бит в указанной позиции
void inversion_bit(int *result, int position) {
  int mask = 1 << position;
  *result = *result ^ mask;
}

// Преобразует целое число в массив двоичных чисел
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

// Устранитель лишних нулей в дробной части и выделяет целую часть
s21_decimal s21_dec_div(s21_decimal value, s21_decimal result) {
  int temp0, temp1, i = 0, part;
  temp1 = value.bits[2] % 10;
  temp0 = value.bits[1] % 10;
  value.bits[2] /= 10;
  value.bits[1] /= 10;
  value.bits[0] /= 10;
  part = value.bits[1];
  while (part > 0) {
    i++;
    part /= 10;
  }
  value.bits[1] += pow(10, i) * temp1;
  i = 0;
  part = value.bits[0];
  while (part > 0) {
    i++;
    part /= 10;
  }
  value.bits[0] += pow(10, i) * temp0;
  for (int i = 0; i < 3; i++) {
    result.bits[i] = value.bits[i];
  }
  return result;
}

// Выделяет дробную часть
s21_decimal s21_help_sub(s21_decimal full, s21_decimal integ, s21_decimal result) {
  for (int i = 0; i < 3; i++) {
    full.bits[i] -= integ.bits[i];
    result.bits[i] = full.bits[i];
  }
  return result;
}

/* А эта функция умножает на 10, нужна для твоего вычитания, чтобы соединить целую и дробную части
Но она лишь умножает на 10, тебе нужно написать цикл, посчитать количество разрядов в дробной части,
чтобы на это число домножить целую часть и вписать туда дробную. Но нужны всякие проверки на
переполнение, вдруг дробь бесконечная к примеру Эту функцию нужно использовать в другом цикле, после
цикла с подсчетом разрядов дробной части
*/
s21_decimal s21_dec_mul(s21_decimal value, s21_decimal result) {
  int temp1, temp2, i = 0, part;
  if (value.bits[0] >= pow(10, 9)) {
    while (value.bits[0] > 0) {
      temp1 = value.bits[0] % 10;
      value.bits[0] /= 10;
      i++;
    }
    value.bits[0] -= temp1 * pow(10, i);
  }
  value.bits[0] *= 10;
  i = 0;
  if (value.bits[1] >= pow(10, 9)) {
    while (value.bits[1] > 0) {
      temp2 = value.bits[1] % 10;
      value.bits[1] /= 10;
      i++;
    }
    value.bits[1] -= temp2 * pow(10, i);
  }
  value.bits[1] *= 10 + temp1;
  // здесь нужна проверка на переполнение
  value.bits[2] *= 10 + temp2;
  return result;
}
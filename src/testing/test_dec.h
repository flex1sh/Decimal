#ifndef TESTING_TEST_DEC_H
#define TESTING_TEST_DEC_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_decimal.h"

typedef struct {
  char name[100];
  struct b1 {
    char name[100];
    s21_decimal bits;
    char bits_bool[4][100];
  } b1;
  struct b2 {
    char name[100];
    s21_decimal bits;
    char bits_bool[4][100];
  } b2;
  struct cs_result {
    char name[100];
    s21_decimal bits;
    char bits_bool[4][100];
  } cs_result;
  struct s21_result {
    char name[100];
    s21_decimal bits;
    char bits_bool[4][100];
  } s21_result;
} test_dec;

char *bool_format(int number);
void print_bool(test_dec dec);
int scan_file(test_dec *dec);
int same_s21_cs(int *s21, int *cs);
void s21_result_print(test_dec dec);
void s21_result_in_dec(test_dec *dec, int len);

#endif  // TESTING_TEST_DEC_H
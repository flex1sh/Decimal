#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_decimal.h"

typedef struct {
  char name[10];
  struct b1 {
    char name[10];
    int bits[4];
    char bits_str[4][100];
  } b1;
  struct b2 {
    char name[10];
    int bits[4];
    char bits_str[4][100];
  } b2;
  struct cs_result {
    char name[10];
    int bits[4];
    char bits_str[4][100];
  } cs_result;
  struct s21_result {
    char name[10];
    int bits[4];
    char bits_str[4][100];
  } s21_result;
} dec_fun;

char *bool_format(unsigned int number, char *str) {
  for (int i = 0; i < 32; i++) {
    str[i] = number >> 31 - i << 31 ? '1' : '0';
  }
  return str;
}
void print_bool(dec_fun dec) {
  char str[33] = {0};
  if (dec.b1.name && dec.b2.name) {
    if (dec.b1.bits[3] || dec.b2.bits[3]) {
      printf("\nbits1[%d]:%s\n", 3, bool_format(dec.b1.bits[3], str));
      printf("bits2[%d]:%s\n\n", 3, bool_format(dec.b2.bits[3], str));
    }

    if (dec.b1.bits[2] || dec.b2.bits[2]) {
      printf("bits1[%d]:%s\n", 2, bool_format(dec.b1.bits[2], str));
      printf("bits2[%d]:%s\n\n", 2, bool_format(dec.b2.bits[2], str));
    }

    if (dec.b1.bits[1] || dec.b2.bits[1]) {
      printf("bits1[%d]:%s\n", 1, bool_format(dec.b1.bits[1], str));
      printf("bits2[%d]:%s\n\n", 1, bool_format(dec.b2.bits[1], str));
    }

    if (dec.b1.bits[0] || dec.b2.bits[0]) {
      printf("bits1[%d]:%s\n", 0, bool_format(dec.b1.bits[0], str));
      printf("bits2[%d]:%s\n\n", 0, bool_format(dec.b2.bits[0], str));
    }
  }
}

int scan_file(dec_fun dec[100]) {
  FILE *myfile;
  int i = 0;
  myfile = fopen("result_cs.txt", "r");
  char buffer[1024];
  char arr_line[100][100] = {0};
  for (i = 0; fgets(buffer, 1024, myfile) != NULL; i++) {
    int j = 0;
    char *str = buffer;
    char *token = strtok(str, "|");
    for (; token != NULL; j++) {
      strcpy(arr_line[j], token);
      token = strtok(NULL, "|");
    }
    strcpy(dec[i].name, arr_line[0]);

    strcpy(dec[i].b1.name, arr_line[1]);
    strcpy(dec[i].b1.bits_str[3], arr_line[2]);
    strcpy(dec[i].b1.bits_str[2], arr_line[3]);
    strcpy(dec[i].b1.bits_str[1], arr_line[4]);
    strcpy(dec[i].b1.bits_str[0], arr_line[5]);

    strcpy(dec[i].b2.name, arr_line[6]);
    strcpy(dec[i].b2.bits_str[3], arr_line[7]);
    strcpy(dec[i].b2.bits_str[2], arr_line[8]);
    strcpy(dec[i].b2.bits_str[1], arr_line[9]);
    strcpy(dec[i].b2.bits_str[0], arr_line[10]);

    strcpy(dec[i].cs_result.name, arr_line[11]);
    strcpy(dec[i].cs_result.bits_str[3], arr_line[12]);
    strcpy(dec[i].cs_result.bits_str[2], arr_line[13]);
    strcpy(dec[i].cs_result.bits_str[1], arr_line[14]);
    strcpy(dec[i].cs_result.bits_str[0], arr_line[15]);

    for (int k = 0; k < 4; k++) {
      dec[i].b1.bits[k] = atoi(dec[i].b1.bits_str[k]);
      dec[i].b2.bits[k] = atoi(dec[i].b2.bits_str[k]);
      dec[i].cs_result.bits[k] = atoi(dec[i].cs_result.bits_str[k]);
    }

    printf("%s (%s  %s): %s\n", dec[i].name, dec[i].b1.name, dec[i].b2.name, dec[i].cs_result.name);

    print_bool(dec[i]);
  }

  fclose(myfile);
  return i;
}

int main(void) {
  dec_fun dec[100] = {0};
  int len_dec_fun = scan_file(dec);
  for (size_t i = 0; i < len_dec_fun; i++) {
    print_bool(dec[i]);
  }

  return 0;
}
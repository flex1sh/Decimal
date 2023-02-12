#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "test_dec.h"

typedef struct {
  char name[100];
  struct b1 {
    char name[100];
    int bits[4];
    char bits_bool[4][100];
  } b1;
  struct b2 {
    char name[100];
    int bits[4];
    char bits_bool[4][100];
  } b2;
  struct cs_result {
    char name[100];
    int bits[4];
    char bits_bool[4][100];
  } cs_result;
  struct s21_result {
    char name[100];
    int bits[4];
    char bits_bool[4][100];
  } s21_result;
} test_dec;

char *bool_format(int number) {
  static char str[32] = {0};
  for (int i = 0; i < 32; i++) {
    str[i] = number >> 31 - i << 31 ? '1' : '0';
  }
  return str;
}
void print_bool(test_dec dec) {
  if (dec.b1.name && dec.b2.name) {
    printf("%s (%s  %s): %s\n", dec.name, dec.b1.name, dec.b2.name, dec.cs_result.name);
    for (int i = 3; i >= 0; i--) {
      if (dec.b1.bits[i] || dec.b2.bits[i] || dec.cs_result.bits[i]) {
        printf("  bits1 [%d]:%s  : %d\n", i, dec.b1.bits_bool[i], dec.b1.bits[i]);
        printf("  bits2 [%d]:%s  : %d\n", i, dec.b2.bits_bool[i], dec.b2.bits[i]);
        printf("  result[%d]:%s  : %d\n\n", i, dec.cs_result.bits_bool[i], dec.cs_result.bits[i]);
      }
    }
  }
}

int scan_file(test_dec dec[100]) {
  FILE *myfile;
  int i = 0;
  myfile = fopen("result_cs.txt", "r");
  char buffer[1024];
  char arr_line[100][100] = {0};
  for (i = 0; fgets(buffer, 1024, myfile) != NULL; i++) {
    char *str = buffer;
    char *token = strtok(str, "|");
    for (int j = 0; token != NULL; j++) {
      strcpy(arr_line[j], token);
      token = strtok(NULL, "|");
    }
    strcpy(dec[i].name, arr_line[0]);

    strcpy(dec[i].b1.name, arr_line[1]);
    dec[i].b1.bits[3] = atoi(arr_line[2]);
    dec[i].b1.bits[2] = atoi(arr_line[3]);
    dec[i].b1.bits[1] = atoi(arr_line[4]);
    dec[i].b1.bits[0] = atoi(arr_line[5]);

    strcpy(dec[i].b2.name, arr_line[6]);
    dec[i].b2.bits[3] = atoi(arr_line[7]);
    dec[i].b2.bits[2] = atoi(arr_line[8]);
    dec[i].b2.bits[1] = atoi(arr_line[9]);
    dec[i].b2.bits[0] = atoi(arr_line[10]);

    strcpy(dec[i].cs_result.name, arr_line[11]);
    dec[i].cs_result.bits[3] = atoi(arr_line[12]);
    dec[i].cs_result.bits[2] = atoi(arr_line[13]);
    dec[i].cs_result.bits[1] = atoi(arr_line[14]);
    dec[i].cs_result.bits[0] = atoi(arr_line[15]);

    for (int k = 0; k < 4; k++) {
      strcpy(dec[i].b1.bits_bool[k], bool_format(dec[i].b1.bits[k]));
      strcpy(dec[i].b2.bits_bool[k], bool_format(dec[i].b2.bits[k]));
      strcpy(dec[i].cs_result.bits_bool[k], bool_format(dec[i].cs_result.bits[k]));
    }
    // print_bool(dec[i]);
  }

  fclose(myfile);
  return i;
}

int main(void) {
  test_dec dec[100] = {0};
  int len_dec_fun = scan_file(dec);

  for (size_t i = 0; i < len_dec_fun; i++) {
    print_bool(dec[i]);
  }

  return 0;
}
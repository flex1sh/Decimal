#include "test_dec.h"

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
      if (dec.b1.bits.bits[i] || dec.b2.bits.bits[i] || dec.cs_result.bits.bits[i]) {
        printf("  bits1     [%d]:%s  : %d\n", i, dec.b1.bits_bool[i], dec.b1.bits.bits[i]);
        printf("  bits2     [%d]:%s  : %d\n", i, dec.b2.bits_bool[i], dec.b2.bits.bits[i]);
        printf("  result    [%d]:%s  : %d\n\n", i, dec.cs_result.bits_bool[i], dec.cs_result.bits.bits[i]);
        if (dec.s21_result.bits.bits[i])
          printf("  s21_result[%d]:%s  : %d\n\n", i, dec.s21_result.bits_bool[i], dec.s21_result.bits.bits[i]);
      }
    }
  }
}

int scan_file(test_dec *dec) {
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
    dec[i].b1.bits.bits[3] = atoi(arr_line[2]);
    dec[i].b1.bits.bits[2] = atoi(arr_line[3]);
    dec[i].b1.bits.bits[1] = atoi(arr_line[4]);
    dec[i].b1.bits.bits[0] = atoi(arr_line[5]);

    strcpy(dec[i].b2.name, arr_line[6]);
    dec[i].b2.bits.bits[3] = atoi(arr_line[7]);
    dec[i].b2.bits.bits[2] = atoi(arr_line[8]);
    dec[i].b2.bits.bits[1] = atoi(arr_line[9]);
    dec[i].b2.bits.bits[0] = atoi(arr_line[10]);

    strcpy(dec[i].cs_result.name, arr_line[11]);
    dec[i].cs_result.bits.bits[3] = atoi(arr_line[12]);
    dec[i].cs_result.bits.bits[2] = atoi(arr_line[13]);
    dec[i].cs_result.bits.bits[1] = atoi(arr_line[14]);
    dec[i].cs_result.bits.bits[0] = atoi(arr_line[15]);

    for (int k = 0; k < 4; k++) {
      strcpy(dec[i].b1.bits_bool[k], bool_format(dec[i].b1.bits.bits[k]));
      strcpy(dec[i].b2.bits_bool[k], bool_format(dec[i].b2.bits.bits[k]));
      strcpy(dec[i].cs_result.bits_bool[k], bool_format(dec[i].cs_result.bits.bits[k]));
    }
  }

  fclose(myfile);
  return i;
}

int same_s21_cs(int *s21, int *cs) {
  int flag = 0;
  for (int i = 0; i < 4; i++) {
    if (s21[i] != cs[i]) {
      flag = 1;
      break;
    }
  }
  return flag;
}

void s21_result_print(test_dec dec) {
  int same = same_s21_cs(dec.s21_result.bits.bits, dec.cs_result.bits.bits);
  printf("%s (%s  %s): %s\n", dec.name, dec.b1.name, dec.b2.name, dec.cs_result.name);
  for (int j = 3; j >= 0; j--) {
    strcpy(dec.s21_result.bits_bool[j], bool_format(dec.s21_result.bits.bits[j]));
    printf("  s21[%d]:%s  : %d\n   cs[%d]:%s  : %d", j, dec.s21_result.bits_bool[j], dec.s21_result.bits.bits[j], j,
           dec.cs_result.bits_bool[j], dec.cs_result.bits.bits[j]);
    j ? printf("\n\n") : printf("\n");
  }
  !same ? printf("\t    ---------OK---------") : printf("\t   !-------FALSE-------!");
  printf("\n\n");
}

void s21_result_in_dec(test_dec *dec, int len) {
  for (int i = 0; i < len; i++) {
    if (!strcmp(dec[i].name, "sub")) {
      s21_sub(dec[i].b1.bits, dec[i].b2.bits, &dec[i].s21_result.bits);
      s21_result_print(dec[i]);
    }

    // if (!strcmp(dec[i].name, "add")) {
    //   s21_add(dec[i].b1.bits, dec[i].b2.bits, &dec[i].s21_result.bits);
    //   s21_result_print(dec[i]);
    // }

    // if (!strcmp(dec[i].name, "mul")) {
    //   s21_mul(dec[i].b1.bits, dec[i].b2.bits, &dec[i].s21_result.bits);
    //   s21_result_print(dec[i]);
    // }

    // if (!strcmp(dec[i].name, "div")) {
    //   s21_div(dec[i].b1.bits, dec[i].b2.bits, &dec[i].s21_result.bits);
    //   s21_result_print(dec[i]);
    // }

    // if (!strcmp(dec[i].name, "mod")) {
    //   s21_mod(dec[i].b1.bits, dec[i].b2.bits, &dec[i].s21_result.bits);
    //   s21_result_print(dec[i]);
    // }
  }
}

int main(void) {
  test_dec dec[100] = {0};
  int len_dec_fun = scan_file(dec);
  s21_result_in_dec(dec, len_dec_fun);
  // for (size_t i = 0; i < len_dec_fun; i++) {
  //   print_bool(dec[i]);
  // }

  return 0;
}
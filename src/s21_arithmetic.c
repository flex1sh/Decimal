#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {  // В работе

  int qwert = 181;  // Переименовать
  int trewq = 0;    // Переименовать
  int current_position_bits_0 = 0;
  int current_position_bits_1 = 0;
  int current_position_bits_2 = 0;
  int check_0 = 0;
  int check_1 = 0;
  int check_2 = 0;
  int check_3 = 0;
  int check_4 = 0;
  int check_5 = 0;

  s21_decimal val_1;
  s21_decimal val_2;
  s21_decimal resultat;

  for (int f = 0; f < 3; f++) {
    val_1.bits[f] = value_1.bits[f];
    val_2.bits[f] = value_2.bits[f];
  }

  int flag_virguile_1 = 0;
  int flag_virguile_2 = 0;
  int virguile_1 = (value_1.bits[3] >> 8) & 255;
  int virguile_2 = (value_2.bits[3] >> 8) & 255;

  // выделяем целую часть,чтобы сравнить только ее
  // for (int start_search_index_0 = 0; start_search_index_0 < 3; start_search_index_0++) {
  //   for (int j = 0; j < 32; j++) {
  //     if (virguile_1 == 0) {
  //       flag_virguile_1 = 1;
  //       break;
  //     }
  //     val_1 = s21_dec_div(val_1, val_1);
  //     virguile_1--;
  //   }
  //   for (int j = 0; j < 32; j++) {
  //     if (virguile_2 == 0) {
  //       flag_virguile_2 = 1;
  //       break;
  //     }
  //     val_2 = s21_dec_div(val_2, val_2);
  //     virguile_2--;
  //   }
  // }

  print_bits(value_1, value_2, *result);  // Печать первоначальных значений

  for (; current_position_bits_0 < 32; current_position_bits_0++) {
    printf("%d - iteration\n", current_position_bits_0);
    if (((val_1.bits[0] >> current_position_bits_0) & 1) == 1) {  // 1 - 0
      if (((val_2.bits[0] >> current_position_bits_0) & 1) == 0) {
        inversion_bit(&result->bits[0], current_position_bits_0);
      }
    } else {
      if (((val_2.bits[0] >> current_position_bits_0) & 1) == 1) {   // 0 - 1
        inversion_bit(&result->bits[0], current_position_bits_0);    // Нужна проверка нашел ли старший бит и только // тогда инвертировать
        int start_search_index_0 = current_position_bits_0 + 1;      // Индест старта поиска старшего бита
        for (; start_search_index_0 < 32; ++start_search_index_0) {  // Поиск старшего бита
          if (((val_1.bits[0] >> start_search_index_0) & 1) == 1) {
            inversion_bit(&val_1.bits[0], start_search_index_0);
            check_0 = 1;
            break;
          }
        }
        if (check_0) {  // Если нашел начинаем инвертировать пока не дойдем до индекса старта поиска
          int invertion_index_0 = start_search_index_0 - 1;
          for (; invertion_index_0 > current_position_bits_0; invertion_index_0--) {
            inversion_bit(&val_1.bits[0], invertion_index_0);
          }
          check_0 = 0;
        } else {  // Иначе переходим в bits[1] и ищем там
          int start_search_index_1 = 0;
          for (; start_search_index_1 < 32; start_search_index_1++) {
            if (((val_1.bits[1] >> start_search_index_1) & 1) == 1) {
              inversion_bit(&val_1.bits[1], start_search_index_1);
              check_1 = 1;
              break;
            }
          }
          if (check_1) {
            int invertion_index_1 = start_search_index_1 - 1;  // Если нашел инвертируем
            for (; invertion_index_1 >= 0; invertion_index_1--) {
              inversion_bit(&val_1.bits[1], invertion_index_1);
            }
            int invertion_index_0_1 = start_search_index_0 - 1;  // И также инвертируем в bits[0] пока не дойдем до индекса старта поиска
            for (; invertion_index_0_1 > current_position_bits_0; invertion_index_0_1--) {
              inversion_bit(&val_1.bits[0], invertion_index_0_1);
            }
            check_1 = 0;
          } else {  // Если не нашел в bits[1] то ищем в bits[2]
            int start_search_index_2 = 0;
            for (; start_search_index_2 < 32; start_search_index_2++) {
              if (((val_1.bits[2] >> start_search_index_2) & 1) == 1) {
                inversion_bit(&val_1.bits[2], start_search_index_2);
                check_2 = 1;
                break;
              }
            }
            if (check_2) {
              int invertion_index_2 = start_search_index_2 - 1;  // Если нашел инвертируем в bits[2]
              for (; invertion_index_2 >= 0; invertion_index_2--) {
                inversion_bit(&val_1.bits[2], invertion_index_2);
              }
              for (int aboba = 31; aboba >= 0; aboba--) {  // Инвертируем bits[1] полностью так как там ничего не нашли | !!!! Переименовать абобу!!!
                inversion_bit(&val_1.bits[1], aboba);
              }
              int invertion_index_0_2 = start_search_index_0 - 1;  // И также инвертируем в bits[0] пока не дойдем до индекса старта поиска
              for (; invertion_index_0_2 > current_position_bits_0; invertion_index_0_2--) {
                inversion_bit(&val_1.bits[0], invertion_index_0_2);
              }
              check_2 = 0;
            }
          }
        }
      }
    }
    print_bits(val_1, val_2, *result);
    print_iteration(qwert, &trewq);
  }
  trewq += 11;
  for (; current_position_bits_1 < 32; current_position_bits_1++) {
    printf("%d - iteration\n", current_position_bits_1);
    if (((val_1.bits[1] >> current_position_bits_1) & 1) == 1) {  // 1 - 0
      if (((val_2.bits[1] >> current_position_bits_1) & 1) == 0) {
        inversion_bit(&result->bits[1], current_position_bits_1);
      }
    } else {
      if (((val_2.bits[1] >> current_position_bits_1) & 1) == 1) {  // 0 - 1
        inversion_bit(&result->bits[1], current_position_bits_1);
        int start_search_index_1_1 = current_position_bits_1 + 1;  // Индекс старта поиска старшего бита в bits[1];
        for (; start_search_index_1_1 < 32; ++start_search_index_1_1) {
          if (((val_1.bits[1] >> start_search_index_1_1) & 1) == 1) {
            inversion_bit(&val_1.bits[1], start_search_index_1_1);
            check_3 = 1;
            break;
          }
        }
        if (check_3) {  // Если нашел начинаем инвертировать пока не дойдем до индекса старта поиска
          int inversion_index_1_1 = start_search_index_1_1 - 1;
          for (; inversion_index_1_1 > current_position_bits_1; inversion_index_1_1--) {
            inversion_bit(&val_1.bits[1], inversion_index_1_1);
          }
          check_3 = 0;
        } else {  // Иначе переходим в bits[2] и ищем там
          int start_search_index_2_2 = 0;
          for (; start_search_index_2_2 < 32; start_search_index_2_2++) {
            if (((val_1.bits[2] >> start_search_index_2_2) & 1) == 1) {
              inversion_bit(&val_1.bits[2], start_search_index_2_2);
              check_4 = 1;
              break;
            }
          }
          if (check_4) {  // Если нашел инвертируем
            int invertion_index_2_2 = start_search_index_2_2 - 1;
            for (; invertion_index_2_2 >= 0; invertion_index_2_2--) {
              inversion_bit(&val_1.bits[2], invertion_index_2_2);
            }
            int invertion_index_1_1_1 = start_search_index_1_1 - 1;
            for (; invertion_index_1_1_1 > current_position_bits_1; invertion_index_1_1_1--) {
              inversion_bit(&val_1.bits[1], invertion_index_1_1_1);
            }
            check_4 = 0;
          }
        }
      }
    }
    print_bits(val_1, val_2, *result);
    print_iteration(qwert, &trewq);
  }
  trewq += 11;
  for (; current_position_bits_2 < 32; current_position_bits_2++) {
    printf("%d - iteration\n", current_position_bits_2);
    if (((val_1.bits[2] >> current_position_bits_2) & 1) == 1) {  // 1 - 0
      if (((val_2.bits[2] >> current_position_bits_2) & 1) == 0) {
        inversion_bit(&result->bits[2], current_position_bits_2);
      }
    } else {
      if (((val_2.bits[2] >> current_position_bits_2) & 1) == 1) {  // 0 - 1
        inversion_bit(&result->bits[2], current_position_bits_2);
        int start_search_index_2_2_2 = current_position_bits_2 + 1;
        for (; start_search_index_2_2_2 < 32; ++start_search_index_2_2_2) {
          if (((val_1.bits[2] >> start_search_index_2_2_2) & 1) == 1) {
            inversion_bit(&val_1.bits[2], start_search_index_2_2_2);
            check_5 = 1;
            break;
          }
        }
        if (check_5) {
          int invertion_index_2_2_2 = start_search_index_2_2_2 - 1;
          for (; invertion_index_2_2_2 > current_position_bits_2; invertion_index_2_2_2--) {
            inversion_bit(&val_1.bits[2], invertion_index_2_2_2);
          }
          check_5 = 0;
        }
      }
    }
    print_bits(val_1, val_2, *result);
    print_iteration(qwert, &trewq);
  }

  // if ((virguile_1 > 0) || (virguile_2 > 0)) {  // Проверка есть ли дробная часть
  //   // !!!!
  //   s21_help_sub(value_1, val_1, val_1);
  //   s21_help_sub(value_2, val_2, val_2);
  // }

  return 0;
}

#ifndef SRC_S21_SMART_CALC_
#define SRC_S21_SMART_CALC_
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef double Data;

typedef struct N {
  double num[10];
  int num_n;  //  number of elements in array with numbers
  char operators[10];
  int operator_n;  //  number of elements in array with operators
} stack;

// sub functions :
int s21_validation(char *data);
void s21_init_parser(char *data);
int s21_is_trigonometry(char c);
void s21_trig_operations(char operation, stack *st);
// void s21_trig_operations(char operation, stack *st, double num);
void s21_crop_str(char *str, int index);
void s21_reverse_stack(stack *st);
int s21_is_number(char a);
int s21_priority(char sign);
void s21_push_operator(stack *st, char c);
void s21_operations(stack *st, char operation);
void s21_init_stack(stack *st);
char s21_pop_operator(stack *st);
void s21_print(stack *st);
int s21_is_num_st_empty(stack *st);
int s21_is_operator_st_empty(stack *st);
double s21_parser(char *data);
// double s21_parser(stack *st);
#endif  // SRC_S21_SMART_CALC_

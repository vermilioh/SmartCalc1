#include "s21_smart_calc.h"

// return 1 if char is equal to one of the math sign: *^+-/ and m for mod
int s21_is_sign(char a) {
  int res = 0;
  char sign[7] = "*^+-/m";
  for (int i = 0; i != 7; i++) {
    if (sign[i] == a) {
      res = 1;
    }
  }
  return res;
}

// return 1 if char is equal to one of numbers 0-9 or .
int s21_is_number(char a) {
  int res = 0;
  char number[15] = "0123456789.,";
  for (int i = 0; i != 11; i++) {
    if (number[i] == a) {
      res = 1;
    }
  }
  return res;
}

void s21_init_stack(stack *st) {
  st->num[0] = '\0';
  st->num_n = 0;
  st->operators[0] = '\0';
  st->operator_n = 0;
}

double s21_pop_number(stack *st) {
  double res = 0.00;
  if (st->num_n > 0) {
    res = st->num[st->num_n - 1];
    st->num[st->num_n - 1] = '\0';
    st->num_n--;
  }
  return res;
}

char s21_pop_operator(stack *st) {
  char res = '0';
  if (st->operator_n > 0) {
    res = st->operators[st->operator_n - 1];
    st->operators[st->operator_n - 1] = '\0';
    st->operator_n--;
  }
  return res;
}

void s21_push_number(stack *st, double n) {
  st->num[st->num_n] = n;
  st->num_n++;
  st->num[st->num_n] = '\0';
}

void s21_push_operator(stack *st, char c) {
  st->operators[st->operator_n] = c;
  st->operator_n++;
  st->operators[st->operator_n] = '\0';
}

void s21_operations(stack *st, char operation) {
  double res = 0.00;
  double op1 = s21_pop_number(st);

  if (s21_is_trigonometry(operation)) {  // trigonometry
    switch (operation) {
      case 'a':
        res = cos(op1);
        break;
      case 'b':
        res = sin(op1);
        break;
      case 'c':
        res = tan(op1);
        break;
      case 'd':
        res = acos(op1);
        break;
      case 'e':
        res = asin(op1);
        break;
      case 'f':
        res = atan(op1);
        break;
      case 'g':
        res = sqrt(op1);
        break;
      case 'j':
        res = log(op1);
        break;
      case 'k':
        res = log10(op1);
        break;
    }
  } else if (s21_is_sign(operation)) {  // simple operations
    double op2 = s21_pop_number(st);
    if (operation == '+') {
      res = op2 + op1;
    } else if (operation == '-') {
      res = op2 - op1;
    } else if (operation == '*') {
      res = op2 * op1;
    } else if (operation == '/') {
      res = op2 / op1;
    } else if (operation == 'm') {
      res = fmod(op2, op1);
    } else if (operation == '^') {
      res = pow(op2, op1);
    }
  }
  s21_push_number(st, res);
}

// plus and minus = 1, mult and div = 2, ^ = 3, func = 4,
int s21_priority(char sign) {
  int priority = 0;
  if (sign == '+' || sign == '-') {
    priority = 1;
  } else if (sign == '*' || sign == '/' || sign == 'm') {
    priority = 2;
  } else if (sign == '^') {
    priority = 3;
  } else if (s21_is_trigonometry(sign)) {  // trigonometry func
    priority = 4;
  } else if (sign == '(') {
    priority = 7;
  }
  return priority;
}

char s21_check_operator(stack *st) {
  char res;
  res = st->operators[st->operator_n - 1];
  return res;
}

int s21_is_trigonometry(char c) {
  int res = 0;
  char signs[13] = "abcdefgjk";
  for (int i = 0; signs[i] != '\0'; i++) {
    if (c == signs[i]) {
      res = 1;
      signs[i + 1] = '\0';
    }
  }
  return res;
}

int s21_is_trigonometry_init(char c) {
  int res = 0;
  char signs[7] = "cstal";
  for (int i = 0; signs[i] != '\0'; i++) {
    if (c == signs[i]) {
      res = 1;
      signs[i + 1] = '\0';
    }
  }
  return res;
}

void s21_init_parser(char *data) {
  for (int i = 0; data[i] != '\0'; i++) {
    if (s21_is_trigonometry_init(data[i]) || data[i] == 'm') {
      int operator_size = 0;
      if (data[i] == 'a') {  // acos, asin, atan
        operator_size = 3;
        switch (data[i + 1]) {
          case 'c':
            data[i] = 'd';
            break;
          case 's':
            data[i] = 'e';
            break;
          case 't':
            data[i] = 'f';
            break;
        }
      } else if (data[i] == 's') {  // sin, sqrt
        switch (data[i + 1]) {
          case 'i':
            data[i] = 'b';
            operator_size = 2;
            break;
          case 'q':
            data[i] = 'g';
            operator_size = 3;
            break;
        }
      } else if (data[i] == 'l') {  // ln,log
        switch (data[i + 1]) {
          case 'n':
            data[i] = 'j';
            operator_size = 1;
            break;
          case 'o':
            data[i] = 'k';
            operator_size = 2;
            break;
        }
      } else if (data[i] == 'c') {  // cos
        operator_size = 2;
        data[i] = 'a';
      } else if (data[i] == 't') {  // tan
        operator_size = 2;
        data[i] = 'c';
      } else if (data[i] == 'm') {  // mod
        data[i] = 'm';
        operator_size = 2;
      }

      i++;
      for (; operator_size != 0; operator_size--) {
        s21_crop_str(data, i);
      }
      if (data[i] == '-') i++;          // minus
      while (s21_is_number(data[i])) {  // extra step for num, not a dig
        i++;
      }
    }
  }
}

void s21_crop_str(char *str, int index) {
  for (; str[index] != '\0'; index++) {
    str[index] = str[index + 1];
  }
}


int s21_is_unary_minus(char now, char prev, stack *st) {
  int res = 0;
  if (s21_is_sign(now) && s21_is_sign(prev)) {
    res = 1;
  } else if (s21_is_sign(now) && s21_is_trigonometry(prev)) {
    res = 1;
  } else if (s21_is_sign(now) && st->num_n == 0) {
    res = 1;
  } else if (s21_is_sign(now) && prev == '(') {
    res = 1;
  }
  return res;
}

int s21_is_minus_or_plus(char sign) {
  int res = 0;
  if (sign == '+' || sign == '-') {
    res = 1;
  }
  return res;
}

// how many iterartions loop will do to overstep letters in trig func's name
int s21_how_many_steps(char *str) {
  int steps = 0;
  char first_letter = *str;
  str++;
  if (first_letter == 's') {
    if (*str == 'i') {
      steps = 3;
    } else if (*str == 'q') {
      steps = 4;
    }
  } else if (first_letter == 'a') {
    steps = 4;

  } else if (first_letter == 'l') {
    if (*str == 'o') {
      steps = 3;
    } else if (*str == 'n') {
      steps = 2;
    }
  } else if (first_letter == 't' || first_letter == 'c') {
    steps = 3;
  }
  return steps;
}

int s21_validation(char *data) {
  int error = 0;
  int left_bracket_count = 0;
  int right_bracket_count = 0;
  if (s21_is_sign(data[0]) && !s21_is_minus_or_plus(data[0])) {  // first sign
    error = 1;
  } else {
    int i = 0;
    for (; data[i] != '\0'; data++) {
      if (!s21_is_number(data[i])) {
        if (data[i] == '(') {
          left_bracket_count += 1;
          if (s21_is_number(data[i - 1])) {
            error = 1;
          } else if (data[i + 1] == ')') {
            error = 1;
          }
        } else if (data[i] == ')') {
          right_bracket_count += 1;
          if (s21_is_sign(data[i - 1])) {
            error = 1;
          } else if (data[i + 1] != ')') {
            if (!s21_is_sign(data[i + 1])) {
              error = 1;
            } else if (data[i + 1] == 'm') {
              error = 1;
            }
          }
        } else if (data[i] == ' ') {
          error = 1;
        } else if (s21_is_trigonometry_init(data[i])) {
          if (!s21_is_sign(data[i - 1]) && data[i - 1] != '(') {
            error = 1;
          } else {
            int steps = s21_how_many_steps(data);
            while (steps != 0) {
              data++;
              steps--;
            }
            if (data[i] != '(') error = 1;
            data--;
          }
        }
      } else if (data[i] == '.') {
        if (s21_is_sign(data[i + 1]) || data[i + 1] == '.') {
          error = 1;
        }
      }
    }
    if (error == 0) {
      if (left_bracket_count != right_bracket_count) {  // different brackets
        error = 1;
      } else if (s21_is_sign(data[i - 1])) {  // last sign in str
        error = 1;
      }
    }
  }
  return error;
}

double s21_parser(char *data) {
  stack st;
  s21_init_stack(&st);
  stack *p_st = &st;

  s21_init_parser(data);  // crop trigonometry
  int i = 0;
  int minus = 0;
  while (data[i] != '\0') {
    if (s21_is_number(data[i])) {
      double res = atof(data);
      if (minus == 1) {
        res *= -1;
        minus = 0;
      }
      s21_push_number(p_st, res);
    }

    while (s21_is_number(data[i])) {  // for number, not a digit
      data++;
    }

    if (s21_is_unary_minus(data[i], data[i - 1], p_st)) {  // unary sign
      if (data[i] == '-') {
        if (s21_is_trigonometry(data[i + 1])) {
          minus = 2;
        } else {
          minus = 1;
        }
      }
      data[i] = 'z';
    }

    if (data[i] != '\0') {
      if (s21_is_sign(data[i]) || s21_is_trigonometry(data[i])) {
        if (p_st->operator_n == 0) {  // push very first sign
          s21_push_operator(p_st, data[i]);
        } else {
          int prior1 = s21_priority(data[i]);
          int prior2 = s21_priority(p_st->operators[p_st->operator_n - 1]);
          if (prior1 > prior2 || prior2 == 7) {
            s21_push_operator(p_st, data[i]);
          } else {  // if sign has lower prior than prev
            s21_operations(p_st, s21_pop_operator(p_st));
            // if sign has same prior after calc:
            if (s21_priority(s21_check_operator(p_st)) >=
                s21_priority(data[i])) {
              s21_operations(p_st, s21_pop_operator(p_st));
            }
            if (minus == 2) {  // minus before trig
              s21_push_number(p_st, s21_pop_number(p_st) * (-1));
              minus = 0;
            }
            s21_push_operator(p_st, data[i]);
          }
        }
      } else {
        if (data[i] == '(') {
          s21_push_operator(p_st, data[i]);
        } else if (data[i] == ')') {
          while (s21_check_operator(p_st) != '(') {
            s21_operations(p_st, s21_pop_operator(p_st));
          }
          s21_pop_operator(p_st);
        }
      }
    }

    data++;
  }

  while (p_st->operator_n != 0) {  // if last sign has lowest prior
    s21_operations(p_st, s21_pop_operator(p_st));
    if (minus == 2) {  // minus before trig
      s21_push_number(p_st, s21_pop_number(p_st) * (-1));
      minus = 0;
    }
  }

  return p_st->num[0];
}

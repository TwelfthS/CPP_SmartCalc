/** \file
@brief Основной файл программы
@details Описание кодов ошибок:
1 - две точки в числе, 2 - ошибка с порядком элементов, 3 - не совпадает
количество скобок, 4 - деление на ноль, 5 - недопустимые символы,
6 - больше 255 символов
*/
#include "parser.h"

#include <cmath>
#include <cstring>
#include <iostream>

#include "calc_element.h"

/*!
Вспомогательный namespace
*/
namespace {
int check_func(std::string string_, int i);
int precedence(char a);
void func_action(std::stack<char>& stack, std::stack<double>& output);
}  // namespace

/*!
Основная фукнция. Проходит по всей строке и преобразует ее
обратной польской нотацией, выполняя операции на ходу
*/
double s21::Model::parser() {
  std::stack<char> stack;     // operators stack
  std::stack<double> output;  // numbers stack
  output.push(0);
  int bracket = 0;  // counts brackets. '(' as +1, ')' as -1
  int dot = 0;      // dot counter
  int e_count = 0;  // exp counter
  std::string number = "";
  int rem_unary = 0;  // remember if prev element is unary
  for (size_t i = 0; i < string_.length() && error_ == 0; i++) {
    i = func_validation(stack, i);  // first check if it's a function,
    // work with it and move i forward if so

    CalcElement current = string_[i];
    if (i != 0 && error_ == 0) {  // compare to previous element to see
                                  // if current can stand after it
      s21::CalcElement prev = string_[i - 1];
      prev.SetUnary(rem_unary);
      error_ = current.CheckPrev(prev);
    }
    if (current.GetElem() == 'x' && error_ == 0) {
      if (rem_unary) {
        x_ *= -1;
        number = "";
      }
      output.push(x_);
    }  // x
    number_validation(current.GetElem(), current.GetType(), current.isUnary(),
                      output, number, &dot, &e_count);  // number
    if (current.GetType() == 'o' && !current.isUnary() && error_ == 0)
      sign_validation(current.GetElem(), stack, output);  // sign
    if (current.GetType() == 'b' && error_ == 0)
      bracket_validation(current.GetElem(), stack, output,
                         &bracket);  // brackets
    if (i + 1 == string_.length() &&
        (current.GetType() == 'o' || current.GetElem() == '(' ||
         current.GetElem() == 'e') &&
        error_ == 0) {  // last element
      error_ = 2;
    }

    if (current.isUnary()) {
      rem_unary = 1;
    } else {
      rem_unary = 0;
    }
  }
  if (number != "" && number != "+" && number != "-" && error_ == 0) {
    output.push(std::stod(number));
  }
  if (bracket != 0 && error_ == 0) error_ = 3;
  while (stack.size() > 0 && error_ == 0) {
    stack_action(output, stack);
  }
  return output.top();
}

/*!
Производит действие с числами a и b используя оператор oper, и в случае ошибки
записывает ее код в error
*/
double s21::Model::action(double a, double b, char oper) {
  double ret = 0;
  if (oper == '+') {
    ret = a + b;
  }
  if (oper == '-') {
    ret = a - b;
  }
  if (oper == '*') {
    ret = a * b;
  }
  if (oper == '/') {
    if (b == 0) {
      error_ = 4;
    } else {
      ret = a / b;
    }
  }
  if (oper == '^') {
    ret = pow(a, b);
  }
  if (oper == '%') {
    if (b == 0) {
      error_ = 4;
    } else {
      ret = fmod(a, b);
    }
  }
  return ret;
}

void s21::Model::stack_action(std::stack<double>& output,
                              std::stack<char>& stack) {
  double last = output.top();
  output.pop();
  double prelast = output.top();
  output.pop();
  output.push(action(prelast, last, stack.top()));
  stack.pop();
}

/*!
Парсит числа, в том числе точки и экспоненциальную запись. Записывает
число в number пока оно не закончилось, затем переносит его в output.
*/
void s21::Model::number_validation(double elem, char type, bool unary,
                                   std::stack<double>& output,
                                   std::string& number, int* dot,
                                   int* e_count) {
  // check dots and e's
  if (elem == '.') {
    *dot = *dot + 1;
  }
  if (*dot > 1) {
    error_ = 1;
  }
  if (elem == 'e') {
    *e_count = *e_count + 1;
  }
  if (*e_count > 1) {
    error_ = 2;
  }

  if ((type == 'n' || unary) && error_ == 0) {  // numbers
    number += elem;
  } else if (number != "" && number != "+" && number != "-") {
    output.push(std::stod(number));
    number = "";
    *dot = 0;
    *e_count = 0;
  }
}

/*!
Записывает оператор elem в stack, либо вызывает функцию action по правилам
обратной польской нотации. В последнем случае записывает результат в  output.
В случае ошибки записывает ее код в error.
*/
void s21::Model::sign_validation(char elem, std::stack<char>& stack,
                                 std::stack<double>& output) {
  while (stack.size() != 0 && precedence(stack.top()) >= precedence(elem)) {
    stack_action(output, stack);
  }
  stack.push(elem);
}

/*!
Производит действия со скобкой по правилам обратной польской нотации, используя
стеки output и stack. bracket считает количество открывающих (+1) и закрывающих
(-1) скобок. В случае ошибки записывает ее код в error.
*/
void s21::Model::bracket_validation(char elem, std::stack<char>& stack,
                                    std::stack<double>& output, int* bracket) {
  if (elem == '(') {
    stack.push(elem);
    *bracket = *bracket + 1;
  }
  if (elem == ')') {
    *bracket = *bracket - 1;
    double last = 0;
    double prelast = 0;
    while (stack.size() > 0 && stack.top() != '(') {
      last = output.top();
      output.pop();
      prelast = output.top();
      output.pop();
      output.push(action(prelast, last, stack.top()));
      stack.pop();
    }
    if (stack.size() == 0) {
      if (error_ == 0) error_ = 3;
    } else if (stack.size() == 1) {
      stack.pop();
    } else {
      stack.pop();
      func_action(stack, output);
    }
  }
}

/*!
Проверяет, является ли i-тый элемент в string_ функцией, и записывает ее код в
stack. В случае ошибки записывает ее код в error.
Возвращает i, на котором остановился в результате своей работы
*/
int s21::Model::func_validation(std::stack<char>& stack, int i) {
  if (i + 3 < (int)string_.length() && string_[i] == 'l' &&
      string_[i + 1] == 'o' && string_[i + 2] == 'g' && string_[i + 3] == '(') {
    if (check_func(string_, i)) error_ = 2;
    i = i + 3;
    stack.push('o');
  }
  if (i + 2 < (int)string_.length() && string_[i] == 'l' &&
      string_[i + 1] == 'n' && string_[i + 2] == '(') {
    if (check_func(string_, i)) error_ = 2;
    i = i + 2;
    stack.push('n');
  }
  if (i + 3 < (int)string_.length() && string_[i] == 's' &&
      string_[i + 1] == 'i' && string_[i + 2] == 'n' && string_[i + 3] == '(') {
    if (check_func(string_, i)) error_ = 2;
    stack.push('s');
    i = i + 3;
  }
  if (i + 3 < (int)string_.length() && string_[i] == 'c' &&
      string_[i + 1] == 'o' && string_[i + 2] == 's' && string_[i + 3] == '(') {
    if (check_func(string_, i)) error_ = 2;
    stack.push('c');
    i = i + 3;
  }
  if (i + 3 < (int)string_.length() && string_[i] == 't' &&
      string_[i + 1] == 'a' && string_[i + 2] == 'n' && string_[i + 3] == '(') {
    if (check_func(string_, i)) error_ = 2;
    stack.push('t');
    i = i + 3;
  }
  if (i + 4 < (int)string_.length() && string_[i] == 'a' &&
      string_[i + 1] == 's' && string_[i + 2] == 'i' && string_[i + 3] == 'n' &&
      string_[i + 4] == '(') {
    if (check_func(string_, i)) error_ = 2;
    stack.push('a');
    i = i + 4;
  }
  if (i + 4 < (int)string_.length() && string_[i] == 'a' &&
      string_[i + 1] == 'c' && string_[i + 2] == 'o' && string_[i + 3] == 's' &&
      string_[i + 4] == '(') {
    if (check_func(string_, i)) error_ = 2;
    stack.push('r');
    i = i + 4;
  }
  if (i + 4 < (int)string_.length() && string_[i] == 'a' &&
      string_[i + 1] == 't' && string_[i + 2] == 'a' && string_[i + 3] == 'n' &&
      string_[i + 4] == '(') {
    if (check_func(string_, i)) error_ = 2;
    stack.push('g');
    i = i + 4;
  }
  if (i + 4 < (int)string_.length() && string_[i] == 's' &&
      string_[i + 1] == 'q' && string_[i + 2] == 'r' && string_[i + 3] == 't' &&
      string_[i + 4] == '(') {
    if (check_func(string_, i)) error_ = 2;
    stack.push('q');
    i = i + 4;
  }
  return i;
}

namespace {
/*!
Данная функция принимает на вход строку и число, и проверяет, чем является i - 1
элемент в этой строке. Возвращает 0 если этот символ может стоять перед
арифметической функцией, и 1 в противоположном случае
*/
int check_func(std::string string_, int i) {
  int ret = 1;
  if (i == 0) {
    ret = 0;
  } else {
    s21::CalcElement prev = string_[i - 1];
    if (prev.GetElem() == '(' || prev.GetType() == 'o') {
      ret = 0;
    }
  }
  return ret;
}

/*!
Находит приоритет переданного оператора
*/
int precedence(char a) {
  int precedence = 0;
  if (a == '+' || a == '-') {
    precedence = 1;
  } else if (a == '*' || a == '/' || a == '%') {
    precedence = 2;
  } else if (a == '^') {
    precedence = 3;
  }
  return precedence;
}

/*!
Вызывает арифм функции в зависимости от крайнего элемента stack, и записывает
результат в output
*/
void func_action(std::stack<char>& stack, std::stack<double>& output) {
  double last = output.top();
  output.pop();
  switch (stack.top()) {
    case 'o':
      output.push(log10(last));
      stack.pop();
      break;
    case 'n':
      output.push(log(last));
      stack.pop();
      break;
    case 's':
      output.push(sin(last));
      stack.pop();
      break;
    case 'c':
      output.push(cos(last));
      stack.pop();
      break;
    case 't':
      output.push(tan(last));
      stack.pop();
      break;
    case 'a':
      output.push(asin(last));
      stack.pop();
      break;
    case 'r':
      output.push(acos(last));
      stack.pop();
      break;
    case 'g':
      output.push(atan(last));
      stack.pop();
      break;
    case 'q':
      output.push(sqrt(last));
      stack.pop();
      break;
    default:
      output.push(last);
  }
}
}  // namespace

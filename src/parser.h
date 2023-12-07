#ifndef CPP_SMARTCALC_SRC_PARSER_H_
#define CPP_SMARTCALC_SRC_PARSER_H_

#include <iostream>
#include <stack>

/*!
Основной namespace
*/
namespace s21 {
/*!
Класс парсера
*/
class Model {
 public:
  // constructors
  Model(){};
  Model(std::string string, double x) {
    this->string_ = string;
    this->x_ = x;
    error_ = 0;
  };
  // methods
  double parser();
  int GetError() { return error_; }

 private:
  std::string string_;
  double x_;
  int error_ = 0;

  double action(double a, double b, char oper);
  void stack_action(std::stack<double>& output, std::stack<char>& stack);
  void number_validation(double elem, char type, bool unary,
                         std::stack<double>& output, std::string& number,
                         int* dot, int* e_count);
  void sign_validation(char elem, std::stack<char>& stack,
                       std::stack<double>& output);
  void bracket_validation(char elem, std::stack<char>& stack,
                          std::stack<double>& output, int* bracket);
  int func_validation(std::stack<char>& stack, int i);
};
}  // namespace s21
#endif

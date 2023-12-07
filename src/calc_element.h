#ifndef CPP_SMARTCALC_SRC_CALC_ELEMENT_H_
#define CPP_SMARTCALC_SRC_CALC_ELEMENT_H_

#include <cstring>
#include <iostream>

namespace s21 {
/*!
Класс описывающий один математический элемент (число, оператор и тд)
*/
class CalcElement {
 public:
  CalcElement(char get) { /*!Делает из переданного чара элемент класса*/
    elem_ = get;
    if (elem_ == '+' || elem_ == '-' || elem_ == '*' || elem_ == '/' ||
        elem_ == '^' || elem_ == '%') {
      type_ = 'o';  // operator
    } else if (isdigit(elem_) || elem_ == '.' || elem_ == 'e') {
      type_ = 'n';  // number
    } else if (elem_ == '(' || elem_ == ')') {
      type_ = 'b';  // bracket
    }
  }
  char GetType() const { return type_; } /*!<Получает тип элемента*/
  char GetElem() const { return elem_; } /*!<Получает значение элемениа*/
  bool isUnary() const {
    return unary_;
  } /*!<Проверяет является ли элемент унарным оператором*/
  void SetUnary(int rem) { /*!Делает элемент унарным оператором*/
    if (rem == 1) {
      unary_ = true;
    }
  }
  int CheckPrev(CalcElement prev);

 private:
  char elem_;
  char type_ = 'u';  // u - unknown
  bool unary_ = false;
};

/*!
Проверяет, может ли prev находиться перед данным элементом, возвращает 0 если
да, и 2 либо 5 если нет (см. коды ошибок)
*/
int CalcElement::CheckPrev(CalcElement prev) {
  int ret = 2;  // 2 or 5 - error, 0 - no error
  if (type_ == 'o') {
    if (prev.elem_ == ')' || (prev.type_ == 'n' && prev.elem_ != 'e') ||
        prev.elem_ == 'x') {
      ret = 0;
    } else if ((prev.elem_ == '(' || prev.type_ == 'o') &&
               prev.unary_ == false && (elem_ == '+' || elem_ == '-')) {
      ret = 0;
      unary_ = true;
    } else if (prev.elem_ == 'e' && (elem_ == '+' || elem_ == '-')) {
      ret = 0;
      unary_ = true;
    }
  } else if (type_ == 'n') {
    if (prev.type_ == 'o' || (prev.type_ == 'n' && prev.elem_ != 'e') ||
        prev.elem_ == '(') {
      if (elem_ == 'e' && prev.type_ != 'n') {
        ret = 2;
      } else {
        ret = 0;
      }
    }
  } else if (elem_ == '(') {
    if ((prev.type_ == 'o' && prev.unary_ == false) || prev.elem_ == '(' ||
        strchr("gnts", prev.elem_) != nullptr) {
      ret = 0;
    }
  } else if (elem_ == ')') {
    if (prev.type_ == 'n' || prev.elem_ == 'x' || prev.elem_ == ')') {
      ret = 0;
    }
  } else if (elem_ == 'x') {
    if (prev.type_ == 'o' || prev.elem_ == '(') {
      ret = 0;
    }
  } else {
    ret = 5;
  }
  return ret;
}
}  // namespace s21

#endif

#ifndef CPP_SMARTCALC_SRC_CONTROLLER_H_
#define CPP_SMARTCALC_SRC_CONTROLLER_H_

#include "parser.h"

namespace s21 {
/*!
Контроллер соединяющий модель и интерфейс
*/
class Controller {
 public:
  Controller(std::string string, double x) {
    Model m(string, x);
    model_ = m;
  }
  int GetError() { return model_.GetError(); }
  double ParserController() { return model_.parser(); }

 private:
  Model model_;
};
}  // namespace s21

#endif  // CONTROLLER_H

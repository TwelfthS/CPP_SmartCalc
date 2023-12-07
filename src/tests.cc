#include <gtest/gtest.h>
#include <math.h>

#include "parser.h"

using namespace s21;

TEST(oper, add) {
  std::string s = "2+2";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(result, 4);
  ASSERT_EQ(error, 0);
}

TEST(oper, add2) {
  std::string s = "2+2-1";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(result, 3);
  ASSERT_EQ(error, 0);
}

TEST(oper, add3) {
  std::string s = "2+2*5";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(result, 12);
  ASSERT_EQ(error, 0);
}

TEST(oper, sub) {
  std::string s = "0-375";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(result, -375);
  ASSERT_EQ(error, 0);
}

TEST(oper, sub2) {
  std::string s = "0-3.75.";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 1);
}

TEST(oper, sub3) {
  std::string s = "3-(2+5)6";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 2);
}

TEST(oper, mul) {
  std::string s = "4.1*2.5";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(result, 10.25);
  ASSERT_EQ(error, 0);
}

TEST(oper, mul2) {
  std::string s = "4.1*+-2.5";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 2);
}

TEST(oper, div) {
  std::string s = "27/4";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(result, 6.75);
  ASSERT_EQ(error, 0);
}

TEST(oper, div2) {
  std::string s = "27/0";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 4);
}

TEST(oper, mod) {
  std::string s = "27%5";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(result, 2);
  ASSERT_EQ(error, 0);
}

TEST(oper, mod2) {
  std::string s = "27%0";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 4);
}

TEST(oper, pow1) {
  std::string s = "3^3*2";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(result, 54);
  ASSERT_EQ(error, 0);
}

TEST(oper, pow2) {
  std::string s = "3*3^2";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(result, 27);
  ASSERT_EQ(error, 0);
}

TEST(other, un_plus) {
  std::string s = "25++.1";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(result, 25.1);
  ASSERT_EQ(error, 0);
}

TEST(other, un_minus) {
  std::string s = "25+-.1";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(result, 24.9);
  ASSERT_EQ(error, 0);
}

TEST(other, iks) {
  std::string s = "7*x*(3+5)";
  double x = -2;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(result, -112);
  ASSERT_EQ(error, 0);
}

TEST(other, iks2) {
  std::string s = "7*-x";
  double x = -2;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(result, 14);
  ASSERT_EQ(error, 0);
}

TEST(other, iks3) {
  std::string s = "7x";
  double x = -2;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 2);
}

TEST(other, brackets_empty) {
  std::string s = "()";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 2);
}

TEST(other, brackets_mismatch) {
  std::string s = "((5+3)+1";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 3);
}

TEST(other, brackets) {
  std::string s = "(8-7)*18";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(result, 18);
  ASSERT_EQ(error, 0);
}

TEST(func, log1) {
  std::string s = "log(x)";
  double x = 100;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(result, 2);
  ASSERT_EQ(error, 0);
}

TEST(func, ln1) {
  std::string s = "ln(x)";
  double x = 3;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  int success = 0;
  if (fabs(result - 1.09861228867) < 0.0000001) {
    success = 1;
  }
  ASSERT_EQ(success, 1);
  ASSERT_EQ(error, 0);
}

TEST(func, sin1) {
  std::string s = "sin(x)";
  double x = 3;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  int success = 0;
  if (fabs(result - 0.14112000806) < 0.0000001) {
    success = 1;
  }
  ASSERT_EQ(success, 1);
  ASSERT_EQ(error, 0);
}

TEST(func, sin2) {
  std::string s = "4sin(x)";
  double x = 3;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 2);
}

TEST(func, sin3) {
  std::string s = "sin(cos(ln(sqrt(log(45.868)))))";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  int success = 0;
  if (fabs(result - 0.8237248) < 0.0000001) {
    success = 1;
  }
  ASSERT_EQ(success, 1);
  ASSERT_EQ(error, 0);
}

TEST(func, cos1) {
  std::string s = "cos(x)";
  double x = 3;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  int success = 0;
  if (fabs(result + 0.9899924966) < 0.0000001) {
    success = 1;
  }
  ASSERT_EQ(success, 1);
  ASSERT_EQ(error, 0);
}

TEST(func, tan1) {
  std::string s = "tan(x)";
  double x = 3;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  int success = 0;
  if (fabs(result + 0.14254654307) < 0.0000001) {
    success = 1;
  }
  ASSERT_EQ(success, 1);
  ASSERT_EQ(error, 0);
}

TEST(func, tan2) {
  std::string s = "((tan(0.333)*0.259/15)%2)^0.15";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  int success = 0;
  if (fabs(result - 0.4638955) < 0.0000001) {
    success = 1;
  }
  ASSERT_EQ(success, 1);
  ASSERT_EQ(error, 0);
}

TEST(func, asin1) {
  std::string s = "asin(x)";
  double x = 0.7;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  int success = 0;
  if (fabs(result - 0.7753974966) < 0.0000001) {
    success = 1;
  }
  ASSERT_EQ(success, 1);
  ASSERT_EQ(error, 0);
}

TEST(func, acos1) {
  std::string s = "acos(x)";
  double x = 0.7;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  int success = 0;
  if (fabs(result - 0.7953988302) < 0.0000001) {
    success = 1;
  }
  ASSERT_EQ(success, 1);
  ASSERT_EQ(error, 0);
}

TEST(func, acos2) {
  std::string s = "acos(-0.06e+1)+asin(0.9)-atan(0.3)";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  int success = 0;
  if (fabs(result - 3.0426102) < 0.0000001) {
    success = 1;
  }
  ASSERT_EQ(success, 1);
  ASSERT_EQ(error, 0);
}

TEST(func, atan1) {
  std::string s = "atan(x)";
  double x = 0.7;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  int success = 0;
  if (fabs(result - 0.6107259644) < 0.0000001) {
    success = 1;
  }
  ASSERT_EQ(success, 1);
  ASSERT_EQ(error, 0);
}

TEST(func, atan2) {
  std::string s = "15+atan(x)";
  double x = 0.7;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  int success = 0;
  if (fabs(result - 15.6107259644) < 0.0000001) {
    success = 1;
  }
  ASSERT_EQ(success, 1);
  ASSERT_EQ(error, 0);
}

TEST(func, sqrt1) {
  std::string s = "sqrt(x)";
  double x = 345;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  int success = 0;
  if (fabs(result - 18.574175621) < 0.0000001) {
    success = 1;
  }
  ASSERT_EQ(success, 1);
  ASSERT_EQ(error, 0);
}

TEST(other, exp1) {
  std::string s = "21e+2+25";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(result, 2125);
  ASSERT_EQ(error, 0);
}

TEST(other, exp_2) {
  std::string s = "21e2+25";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 2);
}

TEST(other, exp3) {
  std::string s = "21e";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 2);
}

TEST(other, exp4) {
  std::string s = "3*e";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 2);
}

TEST(other, exp5) {
  std::string s = "15e+2e+3";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 2);
}

TEST(other, rand) {
  std::string s = "2231wfr";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 5);
}

TEST(errors, err2_1) {
  std::string s = "2+-+-3";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 2);
}

TEST(errors, err2_2) {
  std::string s = "(*5)";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 2);
}

TEST(errors, err2_3) {
  std::string s = "6*)";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 2);
}

TEST(errors, err7) {
  std::string s = "6(2+3)";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 2);
}

TEST(errors, err3) {
  std::string s = "5*7)";
  double x = 0;
  Model model(s, x);
  double result = model.parser();
  int error = model.GetError();
  ASSERT_EQ(error, 3);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
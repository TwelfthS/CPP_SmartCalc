#include "mainwindow.h"

#include "controller.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->zero, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->one, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->two, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->three, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->four, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->five, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->six, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->seven, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->eight, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->nine, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->iks, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->exp, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->minus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->mul, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->div, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->bracket_left, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->bracket_right, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->dot, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pow, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->checkBox, SIGNAL(clicked()), this, SLOT(checkBoxes()));
  connect(ui->checkBox1, SIGNAL(clicked()), this, SLOT(checkBoxes()));
  connect(ui->checkBox2, SIGNAL(clicked()), this, SLOT(checkBoxes()));
  connect(ui->checkBox3, SIGNAL(clicked()), this, SLOT(checkBoxes()));
  connect(ui->checkBox4, SIGNAL(clicked()), this, SLOT(checkBoxes()));
  connect(ui->field, SIGNAL(returnPressed()), this, SLOT(on_eq_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  if (error != 0 || ui->field->text() == "nan" || ui->field->text() == "inf") {
    ui->field->clear();
    error = 0;
  }
  QPushButton *button = (QPushButton *)sender();
  if (ui->checkBox->isChecked()) {
    if (button->text() >= '0' && button->text() <= '9') {
      ui->field_x->setText(ui->field_x->text() + button->text());
    }
    if (button->text() == '.' && !ui->field_x->text().contains('.')) {
      ui->field_x->setText(ui->field_x->text() + button->text());
    }
    if ((button->text() == '+' || button->text() == '-') &&
        ui->field_x->text() == "") {
      ui->field_x->setText(ui->field_x->text() + button->text());
    }
  } else if (ui->checkBox1->isChecked()) {
    if (button->text() >= '0' && button->text() <= '9') {
      ui->x1->setText(ui->x1->text() + button->text());
    }
    if (button->text() == '.' && !ui->x1->text().contains('.')) {
      ui->x1->setText(ui->x1->text() + button->text());
    }
    if ((button->text() == '+' || button->text() == '-') &&
        ui->x1->text() == "") {
      ui->x1->setText(ui->x1->text() + button->text());
    }
  } else if (ui->checkBox2->isChecked()) {
    if (button->text() >= '0' && button->text() <= '9') {
      ui->x2->setText(ui->x2->text() + button->text());
    }
    if (button->text() == '.' && !ui->x2->text().contains('.')) {
      ui->x2->setText(ui->x2->text() + button->text());
    }
    if ((button->text() == '+' || button->text() == '-') &&
        ui->x2->text() == "") {
      ui->x2->setText(ui->x2->text() + button->text());
    }
  } else if (ui->checkBox3->isChecked()) {
    if (button->text() >= '0' && button->text() <= '9') {
      ui->y1->setText(ui->y1->text() + button->text());
    }
    if (button->text() == '.' && !ui->y1->text().contains('.')) {
      ui->y1->setText(ui->y1->text() + button->text());
    }
    if ((button->text() == '+' || button->text() == '-') &&
        ui->y1->text() == "") {
      ui->y1->setText(ui->y1->text() + button->text());
    }
  } else if (ui->checkBox4->isChecked()) {
    if (button->text() >= '0' && button->text() <= '9') {
      ui->y2->setText(ui->y2->text() + button->text());
    }
    if (button->text() == '.' && !ui->y2->text().contains('.')) {
      ui->y2->setText(ui->y2->text() + button->text());
    }
    if ((button->text() == '+' || button->text() == '-') &&
        ui->y2->text() == "") {
      ui->y2->setText(ui->y2->text() + button->text());
    }
  } else {
    QString new_label = ui->field->text() + button->text();
    if (button->text() == "sin" || button->text() == "cos" ||
        button->text() == "tan" || button->text() == "asin" ||
        button->text() == "acos" || button->text() == "atan" ||
        button->text() == "log" || button->text() == "ln" ||
        button->text() == "sqrt")
      new_label = new_label + "(";
    if (ui->field->text().size() < 255) ui->field->setText(new_label);
  }
}

void MainWindow::on_clean_clicked() {
  error = 0;
  if (ui->checkBox->isChecked()) {
    ui->field_x->clear();
  } else if (ui->checkBox1->isChecked()) {
    ui->x1->clear();
  } else if (ui->checkBox2->isChecked()) {
    ui->x2->clear();
  } else if (ui->checkBox3->isChecked()) {
    ui->y1->clear();
  } else if (ui->checkBox4->isChecked()) {
    ui->y2->clear();
  } else {
    ui->field->clear();
  }
}

void MainWindow::on_eq_clicked() {
  double x;
  QString result;
  if (ui->field_x->text() == "") {
    x = 0;
  } else {
    QString temp = ui->field_x->text();
    char *end;
    x = strtod(temp.toUtf8(), &end);
    if (end == temp || *end != '\0') {
      error = 5;
      ui->field_x->setText(QString::number(x));
      x = 0;
    }
  }
  if (ui->field->text().size() <= 255) {
    QByteArray ans = ui->field->text().toLatin1();
    s21::Controller controller(ans.data(), x);
    result = QString::number(controller.ParserController());
    error = controller.GetError();
  } else {
    error = 6;
  }
  if (error == 1) {
    ui->field->setText("Ошибка: две точки у одного числа");
  } else if (error == 2) {
    ui->field->setText("Ошибка: некорректное выражение");
  } else if (error == 3) {
    ui->field->setText("Ошибка: несовпадающее количество скобок");
  } else if (error == 4) {
    ui->field->setText("Ошибка: деление на ноль");
  } else if (error == 5) {
    ui->field->setText("Ошибка: недопустимые символы");
  } else if (error == 6) {
    ui->field->setText("Ошибка: допустимо не более 255 символов");
  } else if (error == 0) {
    ui->field->setText(result);
  } else {
    ui->field->setText("Неизвестная ошибка");
  }
}

void MainWindow::on_back_clicked() {
  int checked = 0;
  if (ui->checkBox->isChecked() || ui->checkBox1->isChecked() ||
      ui->checkBox2->isChecked() || ui->checkBox3->isChecked() ||
      ui->checkBox4->isChecked()) {
    checked = 1;
  }

  if ((error == 0 && ui->field->text() != "nan" &&
       ui->field->text() != "inf") ||
      checked) {
    QString text;
    if (ui->checkBox->isChecked()) {
      text = ui->field_x->text();
    } else if (ui->checkBox1->isChecked()) {
      text = ui->x1->text();
    } else if (ui->checkBox2->isChecked()) {
      text = ui->x2->text();
    } else if (ui->checkBox3->isChecked()) {
      text = ui->y1->text();
    } else if (ui->checkBox4->isChecked()) {
      text = ui->y2->text();
    } else {
      text = ui->field->text();
    }
    QString text1 = text;
    if (text1.size() >= 5) {
      if (text1.last(5) == "atan(" || text1.last(5) == "acos(" ||
          text1.last(5) == "asin(" || text1.last(5) == "sqrt(") {
        text.chop(5);
      }
    }
    if (text1.size() >= 4) {
      if (text1.last(4) == "tan(" || text1.last(4) == "cos(" ||
          text1.last(4) == "sin(" || text1.last(4) == "log(") {
        text.chop(4);
      }
    }
    if (text1.size() >= 3) {
      if (text1.last(3) == "ln(") {
        text.chop(3);
      }
    }
    if (text1 == text && !checked) {
      text.chop(1);
    }
    if (text1 == text && checked && text1.size() != 0) {
      text.chop(1);
    }
    if (ui->checkBox->isChecked()) {
      ui->field_x->setText(text);
    } else if (ui->checkBox1->isChecked()) {
      ui->x1->setText(text);
    } else if (ui->checkBox2->isChecked()) {
      ui->x2->setText(text);
    } else if (ui->checkBox3->isChecked()) {
      ui->y1->setText(text);
    } else if (ui->checkBox4->isChecked()) {
      ui->y2->setText(text);
    } else {
      ui->field->setText(text);
    }
  }
}

void MainWindow::on_graph_clicked() {
  ui->widget->clearGraphs();
  double xBegin = ui->x1->text().toDouble();
  double h = 0.1;
  double xEnd = ui->x2->text().toDouble();
  double yBegin = ui->y1->text().toDouble();
  double yEnd = ui->y2->text().toDouble();
  double X;
  QVector<double> x, y;
  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(yBegin, yEnd);
  QByteArray ans;
  double res;
  int error = 0;
  for (X = xBegin; X <= xEnd; X += h) {
    if (X < 0.0001 && X > -0.0001) X = 0;
    ans = ui->field->text().toLatin1();
    s21::Controller controller(ans.data(), X);
    res = controller.ParserController();
    error = controller.GetError();
    if (error == 0) {
      x.push_back(X);
      y.push_back(res);
    } else if (X == xBegin) {
      break;
    } else {
      y.push_back(qQNaN());
    }
  }
  if ((xBegin == 0 && xEnd == 0) || (yBegin == 0 && yEnd == 0)) {
    ui->field_g->setText("Недопустимые границы");
    ui->scale->setText("");
  } else if (error != 0) {
    ui->field_g->setText("Ошибка в выражении");
    ui->scale->setText("");
  } else {
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    ui->field_g->setText("Успешно");
    ui->scale->setText("Scale: 100%");
  }
}

void MainWindow::checkBoxes() {
  QCheckBox *button = (QCheckBox *)sender();
  int c = 0;
  if (button->isChecked()) {
    c = 1;
  }
  ui->checkBox->setCheckState(Qt::Unchecked);
  ui->checkBox1->setCheckState(Qt::Unchecked);
  ui->checkBox2->setCheckState(Qt::Unchecked);
  ui->checkBox3->setCheckState(Qt::Unchecked);
  ui->checkBox4->setCheckState(Qt::Unchecked);
  if (c == 1) button->setCheckState(Qt::Checked);
}

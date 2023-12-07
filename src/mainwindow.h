#ifndef CPP_SMARTCALC_SRC_MAINWINDOW_H
#define CPP_SMARTCALC_SRC_MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void digits_numbers();

  void on_clean_clicked();

  void on_eq_clicked();

  void on_back_clicked();

  void on_graph_clicked();

  void checkBoxes();

 private:
  int error = 0;
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H

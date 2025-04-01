#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "ui_untitled.h"
#include <QEvent>
#include <QMainWindow>
#include <QTime>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void paintEvent(QPaintEvent *event);

  void SetTime(QTime t);
  QTime GetTime() const;

private:
  Ui::MainWindow *ui;

private slots:
  void updateClock();
  void clickButton();
};

#endif // MAINWINDOW_HPP

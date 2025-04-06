#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "ui_untitled.h"
#include <QEvent>
#include <QMainWindow>
#include <QTime>

class ClockWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit ClockWindow(QWidget *parent = nullptr);
  ~ClockWindow();

  void paintEvent(QPaintEvent *event) override; // 重写基类

  void SetTime(const QTime t);
  QTime GetTime() const;

private:
  Ui::MainWindow *ui;

private slots:
  void updateClock();
  void clickButton();
};

#endif // MAINWINDOW_HPP

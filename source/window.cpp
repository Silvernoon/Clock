#include "window.hpp"
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>
#include <QTime>
#include <QTimeEdit>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this); // 调用 setupUi 函数设置界面

  setWindowTitle("时钟");
  // setFixedSize(300, 300);

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &MainWindow::updateClock);
  timer->start(50); // 毫秒

  connect(ui->pushButton, &QPushButton::clicked, this,
          &MainWindow::clickButton);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, true);

  // 表盘
  painter.setPen(Qt::black);
  painter.setBrush(Qt::white);
  painter.drawEllipse(50, 50, 200, 200);

  int hour = GetTime().hour();
  int minute = GetTime().minute();
  int second = GetTime().second();

  // 计算指针位置
  double hourAngle = (hour % 12 + minute / 60.0) * 30.0; // 每小时30度
  double minuteAngle = (minute + second / 60.0) * 6.0;   // 每分钟6度
  double secondAngle = second * 6.0;                     // 每秒6度

  int w = ui->centralwidget->width() / 2;
  int h = ui->centralwidget->height() / 2;

  painter.translate(w, h); // 将坐标原点移动到窗口中心

  // 绘制时针
  painter.save();
  painter.rotate(hourAngle);
  painter.drawLine(0, 0, 0, -50); // 时针长度为50
  painter.restore();

  // 绘制分针
  painter.save();
  painter.rotate(minuteAngle);
  painter.drawLine(0, 0, 0, -70); // 分针长度为70
  painter.restore();

  // 绘制秒针
  painter.save();
  painter.rotate(secondAngle);
  painter.drawLine(0, 0, 0, -90); // 秒针长度为90
  painter.restore();

  // painter.translate(-w, -h); // 恢复坐标原点

  event->accept();
}

// time
void MainWindow::SetTime(QTime t) { ui->timeEdit->setTime(t); }
QTime MainWindow::GetTime() const { return ui->timeEdit->time(); }

// slots
void MainWindow::updateClock() {
  SetTime(GetTime().addMSecs(50));
  update(); // 重绘
}
void MainWindow::clickButton() { SetTime(QTime::currentTime()); }

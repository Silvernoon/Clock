#include "window.hpp"
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QPushButton>
#include <QTime>
#include <QTimeEdit>
#include <QTimer>
#include <qnamespace.h>

static const int refreshInterval = 50; // 刷新间隔(ms)

ClockWindow::ClockWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this); // 调用 setupUi 函数设置界面

  setWindowTitle("时钟");
  // setFixedSize(300, 300);

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &ClockWindow::updateClock);
  timer->start(refreshInterval); // 毫秒

  connect(ui->pushButton, &QPushButton::clicked, this,
          &ClockWindow::clickButton);
}

ClockWindow::~ClockWindow() { delete ui; }

QRectF textRectF(double radius, int pointSize, double angle) {
  // 计算数字的中心位置
  double x = radius * qCos(angle * M_PI / 180.0);
  double y = radius * qSin(angle * M_PI / 180.0);

  // 根据字体大小计算数字的宽度和高度
  QFontMetrics fontMetrics(QFont("Arial", pointSize));
  int width =
      fontMetrics.horizontalAdvance(QString::number(12)); // 假设数字是两位数
  int height = fontMetrics.height();

  // 返回数字的绘制区域
  return QRectF(x - width / 2.0, y - height / 2.0, width, height);
}

void ClockWindow::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿

  int w = ui->centralwidget->width();
  int h = ui->centralwidget->height();

  painter.translate(w / 2, h / 2); // 将坐标原点移动到窗口中心

  int side = qMin(w, h);
  painter.scale(side / 200.0, side / 200.0);

  // 表盘
  // 绘制表盘外圆
  painter.setPen(Qt::black);                   // 边框
  painter.setBrush(Qt::white);                 // 填充
  painter.drawEllipse(QPoint(0, 0), 100, 100); // 画圆

  painter.save();
  // 绘制时钟刻度线
  painter.setPen(Qt::black);
  for (int i = 0; i < 12; ++i) {
    painter.drawLine(80, 0, 90, 0);
    painter.rotate(30.0);
  }

  // 绘制分钟刻度线
  for (int j = 0; j < 60; ++j) {
    if ((j % 5) != 0) {
      painter.drawLine(92, 0, 96, 0);
    }
    painter.rotate(6.0);
  }

  // 绘制时钟数字
  QFont font = painter.font();
  font.setBold(true);
  painter.setFont(font);
  int pointSize = font.pointSize();

  int radius = 100;
  int nHour = 0;
  for (int i = 0; i < 12; ++i) {
    nHour = i + 3;
    if (nHour > 12) {
      nHour -= 12;
    }
    painter.drawText(textRectF(radius * 0.8, pointSize, i * 30),
                     Qt::AlignCenter, QString::number(nHour));
  }
  painter.restore();

  // 指针
  int hour = GetTime().hour();
  int minute = GetTime().minute();
  int second = GetTime().second();

  // 计算指针位置
  double hourAngle = (hour % 12 + minute / 60.0) * 30.0; // 每小时30度
  double minuteAngle = (minute + second / 60.0) * 6.0;   // 每分钟6度
  double secondAngle = second * 6.0;                     // 每秒6度

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
void ClockWindow::SetTime(const QTime t) { ui->timeEdit->setTime(t); }
QTime ClockWindow::GetTime() const { return ui->timeEdit->time(); }

// slots
// 刷新
void ClockWindow::updateClock() {
  SetTime(GetTime().addMSecs(refreshInterval));
  update(); // 重绘
}
void ClockWindow::clickButton() { SetTime(QTime::currentTime()); }

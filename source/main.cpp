#include "window.hpp"
#include <QApplication>
#include <QIcon>
#include <QTableWidget>
#include <QWidget>
#include <QtContainerFwd>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  ClockWindow window;

  window.SetTime(QTime::currentTime());

  window.show();
  return app.exec();
}

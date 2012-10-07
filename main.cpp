#include "MainWindow.h"
#include <QtGui>

int main(int argc, char *argv[])
{
  QApplication arg(argc, argv);
  MainWindow xx;
  xx.show();
  return arg.exec();
}

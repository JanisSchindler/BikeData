#include "mainwindow.h"
#include <QApplication>
#include "Model/manager.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QString path = argv[0];
  path = path.append(".dat");
  Manager* manager = new Manager(path);
  MainWindow w(manager);
  w.show();

  return a.exec();
}

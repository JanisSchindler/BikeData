#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "UI/riders.h"
#include "UI/tours.h"
#include "Model/manager.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(Manager *manager, QWidget *parent = 0);
  ~MainWindow();

protected:
  void closeEvent(QCloseEvent *bar);

private:
  void init();
  Manager *mManager;
  Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H

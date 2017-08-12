#ifndef RIDERS_H
#define RIDERS_H

#include <QWidget>
#include "Model/manager.h"

namespace Ui {
  class Riders;
}

class Riders : public QWidget
{
  Q_OBJECT

public:
  explicit Riders(Manager *manager, QWidget *parent = 0);
  ~Riders();

private:
  Manager *mManager;
  Ui::Riders *ui;  
};

#endif // RIDERS_H

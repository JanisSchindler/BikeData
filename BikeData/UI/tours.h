#ifndef TOURS_H
#define TOURS_H

#include <QWidget>
#include "Model/manager.h"
#include "Model/tour.h"
#include "Model/rider.h"

namespace Ui {
  class Tours;
}

class Tours : public QWidget
{
  Q_OBJECT

public:
  explicit Tours(Manager *manager, QWidget *parent = 0);
  ~Tours();

private:
  Manager *mManager;
  Ui::Tours *ui;
};

#endif // TOURS_H

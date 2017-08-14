#ifndef RIDERS_H
#define RIDERS_H

#include <QWidget>
#include "idqwidgetlistitem.h"
#include "Model/manager.h"
#include "Model/duration.h"

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
  void setUi(const Rider* rider);
  void setModel(Rider* rider);

private slots:
  void onCurrentRowChanged(int currentRow);
  void onButtonOk();
  void onButtonCancel();
  void onToursChanged();
};

#endif // RIDERS_H

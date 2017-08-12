#ifndef RIDERS_H
#define RIDERS_H

#include <QWidget>

namespace Ui {
  class Riders;
}

class Riders : public QWidget
{
  Q_OBJECT

public:
  explicit Riders(QWidget *parent = 0);
  ~Riders();

private:
  Ui::Riders *ui;
};

#endif // RIDERS_H

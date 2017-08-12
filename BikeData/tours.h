#ifndef TOURS_H
#define TOURS_H

#include <QWidget>

namespace Ui {
  class Tours;
}

class Tours : public QWidget
{
  Q_OBJECT

public:
  explicit Tours(QWidget *parent = 0);
  ~Tours();

private:
  Ui::Tours *ui;
};

#endif // TOURS_H

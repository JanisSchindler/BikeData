
#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString file = QString("tours.dat");

MainWindow::MainWindow(Manager *manager, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  mManager = manager;
  init();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::init()
{
  mManager->load();
  // create 2 simple layouts, add the widgets and assign them to the
  // tab widget's tabs
  QVBoxLayout* layout1 = new QVBoxLayout();
  layout1->addWidget(new Riders(mManager));
  ui->mTabWidget->widget(0)->setLayout(layout1);
  QVBoxLayout* layout2 = new QVBoxLayout();
  layout2->addWidget(new Tours(mManager));
  ui->mTabWidget->widget(1)->setLayout(layout2);
  ui->mTabWidget->setCurrentIndex(0);
}

// save on close
void MainWindow::closeEvent (QCloseEvent *event)
{
  if (NULL != mManager)
  {
    mManager->save();
  }
  event->accept();
}

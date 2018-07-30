#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialogderived.h"
#include "dialogderived2.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     p = new DialogBase();
    //p = new DialogDerived();
   // p = new DialogDerived2();
    ui->verticalLayout->addWidget(p );
}

MainWindow::~MainWindow()
{
    delete ui;
}

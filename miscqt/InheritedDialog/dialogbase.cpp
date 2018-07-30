#include "dialogbase.h"
#include "ui_dialogbase.h"
#include <iostream>
DialogBase::DialogBase(QWidget *parent) :
    QDialog(parent)
  //  ui(new Ui::DialogBase)
{
   // ui->setupUi(this);
}

DialogBase::~DialogBase()
{
   // delete ui;
}

void DialogBase::basedFunc()
{
    std::cout << "print base message" << std::endl;
}

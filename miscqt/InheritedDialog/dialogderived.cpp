#include "dialogderived.h"
#include "ui_dialogderived.h"

DialogDerived::DialogDerived(QWidget *parent) :
    DialogBase(parent),
    ui(new Ui::DialogDerived)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(OnclickedButton()));
}

DialogDerived::~DialogDerived()
{
    delete ui;
}


void DialogDerived::OnclickedButton()
{
    basedFunc();
}

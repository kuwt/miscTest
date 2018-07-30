#include "dialogderived2.h"
#include "ui_dialogderived2.h"

DialogDerived2::DialogDerived2(QWidget *parent) :
    DialogBase(parent),
    ui(new Ui::DialogDerived2)
{
    ui->setupUi(this);
     connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(OnclickedButton()));
}

DialogDerived2::~DialogDerived2()
{
    delete ui;
}

void DialogDerived2::OnclickedButton()
{
    basedFunc();
    basedFunc();
}

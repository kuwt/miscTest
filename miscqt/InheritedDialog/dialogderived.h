#ifndef DIALOGDERIVED_H
#define DIALOGDERIVED_H

#include <QDialog>
#include "dialogbase.h"
namespace Ui {
class DialogDerived;
}

class DialogDerived : public DialogBase
{
    Q_OBJECT

public:
    explicit DialogDerived(QWidget *parent = 0);
    ~DialogDerived();

private slots:
    void OnclickedButton();
private:
    Ui::DialogDerived *ui;
};

#endif // DIALOGDERIVED_H

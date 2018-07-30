#ifndef DIALOGDERIVED2_H
#define DIALOGDERIVED2_H

#include <QDialog>
#include "dialogbase.h"
namespace Ui {
class DialogDerived2;
}

class DialogDerived2 : public DialogBase
{
    Q_OBJECT

public:
    explicit DialogDerived2(QWidget *parent = 0);
    ~DialogDerived2();

private slots:
    void OnclickedButton();

private:
    Ui::DialogDerived2 *ui;
};

#endif // DIALOGDERIVED2_H

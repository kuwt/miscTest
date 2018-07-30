#ifndef DIALOGBASE_H
#define DIALOGBASE_H

#include <QDialog>

namespace Ui {
class DialogBase;
}

class DialogBase : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBase(QWidget *parent = 0);
    ~DialogBase();

protected:
    void basedFunc();

private:
    //Ui::DialogBase *ui;
};

#endif // DIALOGBASE_H

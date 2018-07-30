#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include "model.h"
#include "selectablerect.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void initrun();
    void RemoveRectAndCreateRect();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *pScene;
    QGraphicsPixmapItem *pPixmapItem;
    DefectItemModel* pModel_;
    std::vector<SelectableRect*> vpRectItem;

private slots:
    void rectSelect(int id);
};

#endif // MAINWINDOW_H

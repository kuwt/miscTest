#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QImage>
#include <QPixmap>
#include <QSize>

#include <QPen>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pScene = new QGraphicsScene(this);
    pPixmapItem = new QGraphicsPixmapItem();
    QPixmap pix(700,700);
    pPixmapItem->setPixmap(pix);
    pScene->addItem(pPixmapItem);
    ui->graphicsView->setScene(pScene);

    pModel_ = new DefectItemModel(this);
    // init the tableView
    ui->tableView->horizontalHeader()->show();
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setSelectionBehavior( QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(pModel_);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setSortingEnabled(true);

   connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(initrun()));
}

void MainWindow::initrun()
{
        RemoveRectAndCreateRect();
}

void MainWindow::RemoveRectAndCreateRect()
{
   // qDebug() << "RemoveRectAndCreateRect";
    // delete  rectangle
    for (int i = 0; i < vpRectItem.size(); ++i)
    {
        //vpRectItem.at(i)->hide();
      //  qDebug() << "delete address" << vpRectItem.at(i) ;
        delete vpRectItem.at(i);
    }
    vpRectItem.clear();
    pModel_->setRowCount(0);

     // create 20 rectangle
    QTime time = QTime::currentTime();
     qsrand((uint)time.msec());
    for (int i = 0; i < 20; ++i)
    {
        int id = i;
        int x = rand()%250;
        int y = rand()%250;
        int width = 10;
        int height = 10;

        QRect aRect = QRect(x, y, width, height );
      //  qDebug() << "new rect" << x << " " << y ;
        SelectableRect *pRectItem_ = new SelectableRect(aRect, id, pPixmapItem);
        QPen rectPen;
        rectPen.setColor(QColor(255,255,255));
        pRectItem_->setPen(rectPen);
        pRectItem_->setFlag(QGraphicsItem::ItemIsSelectable);
        connect(pRectItem_, SIGNAL(rectSelected(int)), this, SLOT(rectSelect(int)));

       // qDebug() << "add address" << pRectItem_ ;
        vpRectItem.push_back(pRectItem_);

        pModel_->add_Rect(id, aRect);
    }

}
void  MainWindow::rectSelect(int id)
{
    int N = pModel_->rowCount();
    int row = -1;

    if (0 <= id && id < N)
    {
        int row = id;
         ui->tableView->setCurrentIndex(pModel_->index(row,0));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

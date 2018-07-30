#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QThread>


// Catch QMessage, redirect to cout
 /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
void MainWindow::QMessageOutput(QtMsgType , const QMessageLogContext &, const QString &msg)
{
   std::cout<<msg.toStdString().c_str()<<std::endl;
}
 /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);

     // Set up ThreadLogStream, which redirect cout to signal sendLogString
     // Set up  MessageHandler,  wgucg catch message from sendLogString and Display
     /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    m_qd = new ThreadLogStream(std::cout); //Redirect Console output to QTextEdit
    this->msgHandler = new MessageHandler(this->ui->textEdit, this);
    connect(m_qd, &ThreadLogStream::sendLogString, msgHandler, &MessageHandler::catchMessage);
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/


    connect(ui->pushButtonSameThreadTest, SIGNAL(clicked()),this,SLOT(SameThreadTest()));
    connect(ui->pushButtonCrossThreadTest, SIGNAL(clicked()),this,SLOT(CrossThreadTest()));
}



void MainWindow::SameThreadTest()
{

    std::cout<< "Hello World1" <<std::endl;
    qDebug() << "Hello World1q" ;
}

void MainWindow::CrossThreadTest()
{
    QThread     *workerThread= new QThread;
    ThreadWorker *worker  = new ThreadWorker();
    worker->moveToThread(workerThread);
    connect(workerThread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));

    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    workerThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

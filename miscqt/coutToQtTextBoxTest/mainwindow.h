#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTextEdit>
#include "q_debugstream.h"
namespace Ui {
class MainWindow;
}

class ThreadWorker : public QObject
{
    Q_OBJECT
public:
    ThreadWorker()
    {
    }
private:

signals:

    void finished();

public slots:
    void doWork()
    {

         std::cout<< "Hello World2" <<std::endl;
        qDebug() << "Hello World2q" ;
        emit finished();
    }
};



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // QMessage
     /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
   static  void QMessageOutput(QtMsgType , const QMessageLogContext &, const QString &msg);
   /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

public slots:
    void SameThreadTest();
    void CrossThreadTest();



private:
    Ui::MainWindow *ui;

    // MessageHandler for display and ThreadLogStream for redirecting cout
     /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    MessageHandler *msgHandler = Q_NULLPTR;
      ThreadLogStream* m_qd;
        /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
};

#endif // MAINWINDOW_H

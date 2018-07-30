#include "model.h"


DefectItemModel::DefectItemModel(QObject *parent) : QStandardItemModel(parent)
{
    // prepare the header
    QList<QString> head_data;
    head_data << "#" <<"x" << "y" << "width" << "height";
    setHorizontalHeaderLabels(head_data);
}


void DefectItemModel::add_Rect(int id, QRect item)
{
      // add one defect row at the end
      int N = rowCount();
      setItem(N, 0, new QStandardItem(QString::number(id) ) );
      setItem(N, 1, new QStandardItem(QString::number(item.x())));
      setItem(N, 2, new QStandardItem(QString::number(item.y())));
      setItem(N, 3, new QStandardItem(QString::number(item.width())));
      setItem(N, 4, new QStandardItem(QString::number(item.height())));

}

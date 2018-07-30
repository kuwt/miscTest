#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QStandardItemModel>

class DefectItemModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit DefectItemModel(QObject *parent = 0);

    void DefectItemModel::add_Rect(int id, QRect item);

signals:
    void onItemClick(const QModelIndex &);

};


#endif // MODEL_H

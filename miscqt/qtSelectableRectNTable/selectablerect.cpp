#include "selectablerect.h"

SelectableRect::SelectableRect(const QRectF &rect,  int id, QGraphicsItem *parent) :
    QGraphicsRectItem(rect, parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    uid = id;
}


SelectableRect::~SelectableRect()
{

}

int SelectableRect::GetID()
{
    return uid;

}

QVariant SelectableRect::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange)
    {
        if (value.toBool() == true)
        {
            emit rectSelected(uid);
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

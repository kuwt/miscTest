#ifndef SELECTABLERECT_H
#define SELECTABLERECT_H

#include <QObject>
#include <QGraphicsRectItem>
#include <string>

// set rect selectable and emit selected signal

class SelectableRect : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit SelectableRect(const QRectF & rect,int id , QGraphicsItem *parent = 0);
    virtual ~SelectableRect();
    int GetID();

signals:
    void rectSelected(int id);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    int uid;
};

#endif // SELECTABLERECT_H

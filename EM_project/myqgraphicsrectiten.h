#ifndef MYQGRAPHICSRECTITEN_H
#define MYQGRAPHICSRECTITEN_H

#include <QPainter>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QAbstractGraphicsShapeItem>
#include <QGraphicsItem>


class MyQGraphicsRectItem : public QGraphicsRectItem
{
    //Q_OBJECT
public:
    explicit MyQGraphicsRectItem(const qreal& x,const qreal& y,const int& r);
    ~MyQGraphicsRectItem() = default;
    QRectF boundingRect() const;
    void paint(QPainter* painter,
                const QStyleOptionGraphicsItem* option, QWidget* widget);
    //explicit MyQGraphicsRectIten(qreal x, qreal y, qreal width,
    //                             qreal height, QGraphicsItem *parent = nullptr);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void sick();
    void recover();
    bool isSick();

public:
    virtual void advance(int phase);

signals:


private:
    bool m_sick = false;
    qreal m_x=0;
    qreal m_y=0;
    int r =0;
};

#endif // MYQGRAPHICSRECTITEN_H

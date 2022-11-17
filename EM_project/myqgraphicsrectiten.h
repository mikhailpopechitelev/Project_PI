#ifndef MYQGRAPHICSRECTITEN_H
#define MYQGRAPHICSRECTITEN_H

#include <QPainter>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QAbstractGraphicsShapeItem>
#include <QGraphicsItem>
#include <QTextItem>


class MyQGraphicsRectItem : public QGraphicsRectItem
{
    //Q_OBJECT
public:
    explicit MyQGraphicsRectItem(const qreal& x,const qreal& y,const int& wight,const int& all_v);
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
signals:


private:
    int all_v =0;
    qreal m_x=0;
    qreal m_y=0;
    int wight =0;
    int m_sick =30;
};

#endif // MYQGRAPHICSRECTITEN_H

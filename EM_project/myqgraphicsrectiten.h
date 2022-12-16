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
    void dead();
    void sick();
    void recover();
    void infected();
    void unrecovered();

    bool isSick();
    bool isDead();
    bool isInfectd();
    void print_id();
    bool isRecover();

    int get_day();
    int day_sick = 0;
    int day_recovered = 0;

public:
    virtual void advance(int phase);

signals:


private:
    bool m_infected = false;
    bool m_dead = false;
    bool m_recover = false;
    bool m_sick = false;
    qreal m_x=0;
    qreal m_y=0;
    int r =0;
};

#endif // MYQGRAPHICSRECTITEN_H

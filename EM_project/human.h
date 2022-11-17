#ifndef HUMAN_H
#define HUMAN_H
#include<QGraphicsItem>
#include <QPainter>
#include <QObject>

class Human: public QGraphicsEllipseItem
{
    //Q_OBJECT
public:
    Human(qreal x, qreal y);
    ~Human() = default;
public:
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option, QWidget* widget);
    QRectF boundingRect() const;
    void sicken();
    void recover();
    bool isSick();
//signals:

private:
    bool sick = true;
    qreal m_x;
    qreal m_y;
};

#endif // HUMAN_H

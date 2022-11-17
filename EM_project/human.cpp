#include "human.h"

Human::Human(qreal x, qreal y):QGraphicsEllipseItem()
{
    this->m_x =x;
    this->m_y =y;
}

void Human::paint(QPainter* painter,
                  const QStyleOptionGraphicsItem* option, QWidget* widget){
    if(this->sick==false){
        painter->setBrush(Qt::blue);
        painter->drawEllipse(QRect(m_x,m_y,20,20));
    }else{
        painter->setBrush(Qt::red);
        painter->drawEllipse(QRect(m_x,m_y,20,20));
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Human::boundingRect() const {
    return QRectF(m_x,m_y,20,20);
}

void Human::sicken(){
    this->sick =true;
}

void Human::recover(){
    this->sick =false;
}

bool Human::isSick(){
    return sick;
}

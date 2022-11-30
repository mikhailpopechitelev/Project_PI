#include "myqgraphicsrectiten.h"

//конструктор вершины
MyQGraphicsRectItem::MyQGraphicsRectItem(const qreal& x,const qreal& y,const int& r){
    this->m_x = x;
    this->m_y = y;
    this->r = r;
}

//отрисовка вершины
void MyQGraphicsRectItem::paint(QPainter* painter,
                  const QStyleOptionGraphicsItem* option, QWidget* widget){
    if(!m_sick){
        painter->setBrush(Qt::green);
        painter->drawEllipse(QPoint(m_x,m_y),r,r);
    }
    else{
        painter->setBrush(Qt::red);
        painter->drawEllipse(QPoint(m_x,m_y),r,r);
    }

    //маеросы того, что option, widget не используются
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//выделение отбасти для вершины
QRectF MyQGraphicsRectItem::boundingRect() const {
    return QRectF(m_x-r,m_y-r,2*r,2*r);
}

void MyQGraphicsRectItem::advance(int phase){
    if(phase){
        if(this->isSick()){
            this->setBrush(Qt::red);
        }
    }
}

bool MyQGraphicsRectItem::isSick(){
    return (m_sick==true);
}

void MyQGraphicsRectItem::sick(){
    this->m_sick = true;
}

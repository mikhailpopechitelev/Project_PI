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
    if(m_dead){
        painter->setBrush(Qt::black);
        painter->drawEllipse(QPoint(m_x,m_y),r,r);
    }else{
        if(m_recover){
            painter->setBrush(Qt::blue);
            painter->drawEllipse(QPoint(m_x,m_y),r,r);
        }else{
            if(this->isSick()){
                painter->setBrush(Qt::red);
                painter->drawEllipse(QPoint(m_x,m_y),r,r);
            }else if(this->isInfectd()){
                painter->setBrush(Qt::magenta);
                painter->drawEllipse(QPoint(m_x,m_y),r,r);
            }else{
                painter->setBrush(Qt::green);
                painter->drawEllipse(QPoint(m_x,m_y),r,r);
            }
        }
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
        if(m_dead){
            this->setBrush(Qt::black);
        }else{
            if(m_recover){
                this->setBrush(Qt::blue);
            }else{
                if(this->isSick()){
                    this->setBrush(Qt::red);
                }else if(this->isInfectd()){
                    this->setBrush(Qt::magenta);
                }else{
                    this->setBrush(Qt::green);
                }
            }
        }
    }
}

bool MyQGraphicsRectItem::isSick(){
    return (m_sick==true);
}

void MyQGraphicsRectItem::sick(){
    this->m_sick = true;
    this->m_recover = false;
}

void MyQGraphicsRectItem::recover(){
    this->m_sick = false;
    this->m_recover = true;
    this->m_infected = false;
}

void MyQGraphicsRectItem::print_id(){
    qDebug() << this->m_x << m_y;
}

int MyQGraphicsRectItem::get_day(){
    return this->day_sick;
}

void MyQGraphicsRectItem::dead(){
    this->m_dead = true;
    this->m_sick = false;
    this->m_recover = false;
    this->m_infected = false;
}

void MyQGraphicsRectItem::infected(){
    this->m_infected = true;
}

bool MyQGraphicsRectItem::isDead(){
    return (m_dead==true);
}

bool MyQGraphicsRectItem::isRecover(){
    return (m_recover==true);
}

bool MyQGraphicsRectItem::isInfectd(){
    return (m_infected==true);
}

void MyQGraphicsRectItem::unrecovered(){
    this->m_recover = false;
    this->m_infected = false;
    this->m_sick = false;
}

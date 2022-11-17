#include "myqgraphicsrectiten.h"

MyQGraphicsRectItem::MyQGraphicsRectItem(const qreal& x,const qreal& y,const int& wight,const int& all_v):QGraphicsRectItem(){
    this->m_x = x;
    this->m_y = y;
    this->wight = wight;
    this->all_v = all_v;
}


void MyQGraphicsRectItem::paint(QPainter* painter,
                  const QStyleOptionGraphicsItem* option, QWidget* widget){
    if(wight==0){
        if(m_sick/(wight+1)>=1){
            painter->setBrush(QColor(255,0,0));
            painter->drawEllipse(QPoint(m_x,m_y),(20*wight/(all_v+1))+4,(20*wight/(all_v+1))+4);
        }else{
            painter->setBrush(QColor((255*m_sick/(wight+1)),255-((255*m_sick)/(wight+1)),0));
            painter->drawEllipse(QPoint(m_x,m_y),(20*wight/(all_v+1))+4,(20*wight/(all_v+1))+4);
        }
    }else{
        if(m_sick/(wight)>=1){
            painter->setBrush(QColor(255,0,0));
            painter->drawEllipse(QPoint(m_x,m_y),(20*wight/(all_v+1))+4,(20*wight/(all_v+1))+4);
        }else{
            painter->setBrush(QColor((255*m_sick/wight),255-((255*m_sick)/wight),0));
            painter->drawEllipse(QPoint(m_x,m_y),(20*wight/(all_v+1))+4,(20*wight/(all_v+1))+4);
        }
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


QRectF MyQGraphicsRectItem::boundingRect() const {
    if(all_v!=0){
        return QRectF(m_x-1-20*wight/all_v,m_y-1-20*wight/all_v,40*wight/all_v+8,40*wight/all_v+8);
    }else{
        return QRectF(m_x-20*wight/(all_v+1)-2,m_y-20*wight/(all_v+1)-2,40*wight/(all_v+1)+10,40*wight/(all_v+1)+10);
    }
}

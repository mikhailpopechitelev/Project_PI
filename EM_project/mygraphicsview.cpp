#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QGraphicsScene* scen,QWidget* parent)
    : QGraphicsView{scen,parent}
{
    this->setDragMode(QGraphicsView::ScrollHandDrag);
}

void MyGraphicsView::wheelEvent(QWheelEvent* event)
{
    if(event->modifiers()& Qt::ControlModifier){
        QGraphicsView::wheelEvent(event);
    }else{
        //zoom
        const ViewportAnchor anchor = transformationAnchor();
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        int angle = event->angleDelta().y();
        qreal factor;
        if(angle > 0){
            factor =1.1;
        }else{
            factor =0.9;
        }
        scale(factor,factor);
        setTransformationAnchor(anchor);
    }
}


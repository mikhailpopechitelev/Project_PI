#include "startwidget.h"


StartWidget::StartWidget(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout* HBoxLayout = new QHBoxLayout();
    QVBoxLayout* VBoxLayoutfirst = new QVBoxLayout();
    QVBoxLayout* VBoxLayoutsecond = new QVBoxLayout();
    QPushButton* push = new QPushButton("s");

    //вертикальная расстановка
    VBoxLayoutfirst->addWidget(buttonStart);
    VBoxLayoutfirst->addWidget(buttonChooseFile);
    VBoxLayoutfirst->addWidget(buttonBack);

    //расстановка слева на право
    HBoxLayout->addLayout(VBoxLayoutfirst);

    //добавлене в центр виджета
    /*
    QGraphicsScene* scen = new QGraphicsScene(QRectF(0,0,500,500));
    QGraphicsView* view = new  QGraphicsView(scen);

    view->setRenderHint(QPainter::Antialiasing,true);
    QGraphicsEllipseItem* MyItem = new QGraphicsEllipseItem(10,10,60,60);
    MyItem->setPen(QPen(Qt::black,1,Qt::SolidLine));
    MyItem->setBrush(QBrush(Qt::blue));
    scen->addItem(MyItem);

    //QRectF
    //scen.addEllipse()

    MyItem->setPos(150,150);
    MyItem->setFlags(QGraphicsItem::ItemIsMovable);


    //HBoxLayout->addStretch();
    HBoxLayout->addWidget(view);
    */
    /*
    QWidget* wgt = new QWidget()
    HBoxLayout->addStretch();
    HBoxLayout->addWidget(wgt);
    HBoxLayout->addStretch();
    */
    HBoxLayout->addWidget(view);

    //добавление левой расстановки
    VBoxLayoutsecond->addWidget(push);
    HBoxLayout->addLayout(VBoxLayoutsecond);

    this->setLayout(HBoxLayout);
}

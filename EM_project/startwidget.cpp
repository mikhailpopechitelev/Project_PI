#include "startwidget.h"

StartWidget::StartWidget(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout* HBoxLayout = new QHBoxLayout();
    QVBoxLayout* VBoxLayoutfirst = new QVBoxLayout();
    QVBoxLayout* VBoxLayoutsecond = new QVBoxLayout();
    QPushButton* push = new QPushButton("s");
    animatiomTimer = new QTimer(this);
    stepTimer = new QTimer(this);

    //подключение сигналов для StartWidget
    connect(animatiomTimer,SIGNAL(timeout()),scen,SLOT(advance()));
    connect(stepTimer,SIGNAL(timeout()),this,SLOT(onStepTimer()));

    animatiomTimer->start(1000/24);

    //вертикальная расстановка
    VBoxLayoutfirst->addWidget(buttonStart);
    VBoxLayoutfirst->addWidget(buttonChooseFile);
    VBoxLayoutfirst->addWidget(buttonBack);

    //расстановка слева на право
    HBoxLayout->addLayout(VBoxLayoutfirst);

    //добавлене в центр виджета
    HBoxLayout->addWidget(view);

    //добавление левой расстановки
    VBoxLayoutsecond->addWidget(push);
    HBoxLayout->addLayout(VBoxLayoutsecond);

    this->setLayout(HBoxLayout);
}

void StartWidget::onStepTimer(){
    Vec_Item[rand()%Vec_Item.size()-1]->sick();
    qDebug() << rand()%Vec_Item.size()-1;
}

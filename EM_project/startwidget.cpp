#include "startwidget.h"


StartWidget::StartWidget(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout* HBoxLayout = new QHBoxLayout();
    QVBoxLayout* VBoxLayoutfirst = new QVBoxLayout();
    QVBoxLayout* VBoxLayoutsecond = new QVBoxLayout();

    //connect(buttonBack,SIGNAL(clicked()),this,SLOT(slotButtonBack()));
    //вертикальная расстановка
    VBoxLayoutfirst->addWidget(buttonStart);
    VBoxLayoutfirst->addWidget(buttonChooseFile);
    VBoxLayoutfirst->addWidget(buttonBack);

    //расстановка слева на право
    HBoxLayout->addLayout(VBoxLayoutfirst);
    QWidget* wgt = new QWidget();


    //добавлене в центр виджета
    HBoxLayout->addStretch();
    HBoxLayout->addWidget(wgt);
    HBoxLayout->addStretch();

    //добавление левой расстановки
    HBoxLayout->addLayout(VBoxLayoutsecond);

    this->setLayout(HBoxLayout);
}


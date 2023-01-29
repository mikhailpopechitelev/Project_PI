#include<autors.h>

Authors::Authors(QWidget *parent)
    : QWidget{parent}
{
    //!инициализация кнопки
    buttonBack_a = new QPushButton("Back");
    connect(buttonBack_a,SIGNAL(clicked()),parent,SLOT(slotButtonBack()));

    //!инициализация расстановки кнопок
    QHBoxLayout* HBoxLayout = new QHBoxLayout();
    QVBoxLayout* buttonBox = new QVBoxLayout();

    buttonBox->addWidget(buttonBack_a);
    HBoxLayout->addLayout(buttonBox);
    this->setLayout(HBoxLayout);
}

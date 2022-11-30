#include "autors.h"
#include<em_proj.h>

Authors::Authors(QWidget *parent)
    : QWidget{parent}
{
    buttonBack = new QPushButton("Back");
    QVBoxLayout* buttonBox = new QVBoxLayout();
    buttonBox->addWidget(buttonBack);

    connect(buttonBack,SIGNAL(clicked()),parent,SLOT(slotButtonBack()));

    this->setLayout(buttonBox);
    this->resize(800,600);
}

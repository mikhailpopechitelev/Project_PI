#include<autors.h>

Authors::Authors(QWidget *parent)
    : QWidget{parent}
{
    this->buttonBack = new QPushButton("Back");
    QVBoxLayout* buttonBox = new QVBoxLayout();

    //connect(buttonBack,SIGNAL(clicked()),parent,SLOT(slotButtonBack()));

    buttonBox->addWidget(buttonBack);
    this->setLayout(buttonBox);
}

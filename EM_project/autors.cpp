#include "autors.h"

Authors::Authors(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* buttonBox = new QVBoxLayout();
    buttonBox->addWidget(buttonBack);

    this->setLayout(buttonBox);
    this->resize(800,600);
}

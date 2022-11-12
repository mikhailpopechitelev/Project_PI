#include "menu.h"

Menu::Menu(QWidget *parent)
    : QWidget{parent}
{

    QVBoxLayout* buttonBox = new QVBoxLayout();
    buttonBox->addWidget(start);
    buttonBox->addWidget(authors);
    buttonBox->addWidget(quit);
    this->setLayout(buttonBox);
    this->resize(800,600);
}

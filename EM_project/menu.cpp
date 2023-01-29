#include "menu.h"

Menu::Menu(QWidget *parent)
    : QWidget{parent}
{
    //!поля стартового приложения
    start = new QPushButton("Старт");
    quit = new QPushButton("Выход");

    //!подключение кнопок меню
    connect(start,SIGNAL(clicked()),parent,SLOT(slotButtonStart()));
    //connect(authors,SIGNAL(clicked()),parent,SLOT(SlotButtonAutors()));
    connect(quit,SIGNAL(clicked()),parent,SLOT(SlotButtonQuite()));

    //!расположение кнопок в стартовом меню (Старт и Выход)
    QVBoxLayout* buttonBox = new QVBoxLayout();
    buttonBox->addWidget(start);
    //buttonBox->addWidget(authors);
    buttonBox->addWidget(quit);
    this->setLayout(buttonBox);
}

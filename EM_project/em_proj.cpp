#include "em_proj.h"
#include <QLayout>

EM_proj::EM_proj(QWidget *parent)
    : QWidget{parent}
{

    QVBoxLayout* buttonBox = new QVBoxLayout();
    QPushButton* start = new QPushButton("Start");
    QPushButton* authors = new QPushButton("Authors");
    QPushButton* quit = new QPushButton("Quit");
    buttonBox->addWidget(start);
    buttonBox->addWidget(authors);
    buttonBox->addWidget(quit);
    this->setLayout(buttonBox);

}

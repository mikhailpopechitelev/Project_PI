#include "em_proj.h"


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
    QWidget* menu = new QWidget();
    menu->setLayout(buttonBox);
    //this->setLayout(buttonBox);
    menu->resize(1920,1080);

    QWidget* startWidget = new QWidget();
    QWidget* authorsWidget = new QWidget();
    //QWidget*  = new QWidget();


    QStackedWidget* stack = new QStackedWidget();
    stack->addWidget(menu);
    stack->addWidget(startWidget);
    stack->addWidget(authorsWidget);



    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(stack);
    this->setLayout(layout);


    QComboBox* pageComboBox = new QComboBox();
    pageComboBox->addItem(tr("page1"));
    pageComboBox->addItem(tr("page2"));
    pageComboBox->addItem(tr("page3"));

    connect(pageComboBox, &QComboBox::activated, stack, &QStackedWidget::setCurrentIndex);
}

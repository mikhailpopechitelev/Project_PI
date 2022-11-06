#include "em_proj.h"
#include "menu.h"
#include "startwidget.h"
//#include "autors.h"
//#include "startwidget.h"

EM_proj::EM_proj(QWidget *parent)
    : QWidget{parent}
{

    Menu* startmenu = new Menu();
    Authors* authorsWidget = new Authors();
    StartWidget* startWidget = new StartWidget();


    connect(startmenu->start,SIGNAL(clicked()),this,SLOT(slotButtonStart()));
    //Создание и заполнение стека
    //QStackedWidget* stack = new QStackedWidget();
    stack->addWidget(startmenu);
    stack->addWidget(authorsWidget);
    stack->addWidget(startWidget);



    //размещение стека в окне
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(stack);
    this->setLayout(layout);

    //stack->removeWidget(startmenu);
    /*
    QComboBox* pageComboBox = new QComboBox();
    pageComboBox->addItem(tr("page1"));
    pageComboBox->addItem(tr("page2"));
    pageComboBox->addItem(tr("page3"));

    connect(pageComboBox, &QComboBox::activated, stack, &QStackedWidget::setCurrentIndex);
    */

}

void EM_proj::slotButtonStart(){
    //wgt.update()
    qDebug() << stack->count();
    /*
    stack->addWidget(&autorsWidget);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(stack);
    this->repaint();
    this->setLayout(layout);
    //stack->addWidget(&autorsWidget);
    */
    stack->addWidget(&autorsWidget);
    stack->setCurrentWidget(&autorsWidget);
}


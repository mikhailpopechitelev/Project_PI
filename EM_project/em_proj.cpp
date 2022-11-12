#include "em_proj.h"
#include "menu.h"
#include "startwidget.h"
#include <QFileDialog>
#include <QtCore>


EM_proj::EM_proj(QWidget *parent)
    : QWidget{parent}
{
    //Заполнение стека
    stack = new QStackedWidget();
    stack->addWidget(startmenu);

    //подключение кнопок приложения
    connect(startmenu->start,SIGNAL(clicked()),this,SLOT(slotButtonStart()));
    connect(startmenu->authors,SIGNAL(clicked()),this,SLOT(SlotButtonAutors()));
    connect(startmenu->quit,SIGNAL(clicked()),this,SLOT(SlotButtonQuite()));
    connect(startWidget->buttonBack,SIGNAL(clicked()),this,SLOT(slotButtonBack()));
    connect(startWidget->buttonChooseFile,SIGNAL(clicked()),this,SLOT(slotButtonChoose()));

    connect(authorsWidget->buttonBack,SIGNAL(clicked()),this,SLOT(slotButtonBack()));
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(stack);
    this->setLayout(layout);
}

void EM_proj::slotButtonBack(){
    QWidget* wgt = stack->currentWidget();
    stack->removeWidget(wgt);
    stack->setCurrentWidget(stack->currentWidget());
}

//методы заполнения стека и удаления из стека
void EM_proj::pushStack(QWidget* wgt){
    stack->addWidget(wgt);
}
void EM_proj::popStack(){
    QWidget* wgt = stack->currentWidget();
    stack->removeWidget(wgt);
}

//реализация словот кнопок
void EM_proj::slotButtonStart(){
    stack->addWidget(startWidget);
    stack->setCurrentWidget(startWidget);

}
void EM_proj::SlotButtonAutors(){
    stack->addWidget(authorsWidget);
    stack->setCurrentWidget(authorsWidget);
}
void EM_proj::SlotButtonQuite(){
    qApp->quit();
}
void EM_proj::slotButtonChoose(){
    QString url;
    url = QFileDialog::getOpenFileName(this,"Выбрать файл","C:\\",
                                       "All Files (*.*);; GRAPH (*.graph);");

}

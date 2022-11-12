#include "em_proj.h"
#include "menu.h"
#include "startwidget.h"
//#include "Graph_parser.cpp"
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
    std::string URL = url.toStdString();
    loadfile(URL);
}
void EM_proj::loadfile(const std::string& URL){
    startWidget->view->setRenderHint(QPainter::Antialiasing,true);

    QGraphicsEllipseItem* MyItem = CreateItamVerties(10,10,15,QPen(Qt::black,1,Qt::SolidLine),QBrush(Qt::blue));
    startWidget->scen->addItem(MyItem);
    MyItem->setFlags(QGraphicsItem::ItemIsMovable);
}

/*
QGraphicsItem* EM_proj::CreateItamEdges(const int& from,const int& to){
    QGraphicsItem* MyItem = new QGraphicsItem(10,10);
    return MyItem;
}
*/

QGraphicsEllipseItem* EM_proj::CreateItamVerties(const int& x,const int& y, const int& r ,const QPen& pen, const QBrush& brush){
    QGraphicsEllipseItem* MyItem = new QGraphicsEllipseItem(x,y,2*r,2*r);
    MyItem->setPen(pen);
    MyItem->setBrush(brush);
    return MyItem;
}

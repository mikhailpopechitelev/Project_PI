#include "em_proj.h"
#include "menu.h"
#include "startwidget.h"
#include "graph_parser.h"
#include <QFileDialog>
#include <QtCore>
#include <QDebug>

//создание конструктора
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

//методы заполнения стека и удаления из стека
void EM_proj::pushStack(QWidget* wgt){
    stack->addWidget(wgt);
}
void EM_proj::popStack(){
    QWidget* wgt = stack->currentWidget();
    stack->removeWidget(wgt);
}

//реализация словот кнопок
void EM_proj::slotButtonBack(){
    QWidget* wgt = stack->currentWidget();
    stack->removeWidget(wgt);
    stack->setCurrentWidget(stack->currentWidget());
}
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


    //получает ссылку на файл и приводит её к типу строки
    QString url;
    url = QFileDialog::getOpenFileName(this,"Выбрать файл","C:\\",
                                       "All Files (*.*);; GRAPH (*.graph);");
    std::string URL = url.toStdString();
    if(URL != ""){
        qDebug() << url;

        //загружет изначальный граф в сцену
        loadfile(URL);

        //создает массив вершин и ребер находит минимальные точки
        //устанавливает прямоугольник в минимальную точку графа по x и по y с длинами сторон len_x и len_y
        //устанавливает граф по центру
        std::pair<std::vector<Edges>,std::vector<Vertices>> masVE = getMasVE(URL);
        std::vector<std::pair<int,int>> mas =findMinPointMaxPoint(masVE);
        int len_x =mas[0].second-mas[0].first; int len_y = mas[1].second-mas[1].first; int min_x =mas[0].first; int min_y =mas[1].first;
        startWidget->scen->setSceneRect(min_x,min_y,len_x,len_y);

        startWidget->view->resetTransform();
        //скалирует изображение в зависимости от размеров окна
        int size_x = startWidget->view->width();; int size_y =startWidget->view->height();;
        double scale = std::min((size_x/len_x),(size_y/len_y));
        if(scale>=1){
            startWidget->view->scale(scale*0.8,scale*0.8);
        }else{
            scale =std::max((len_x/size_x)+1,(len_y/size_y)+1);
            startWidget->view->scale((1/scale),(1/scale));
        }
    }

}

//загрузка на сцену графа из файла
void EM_proj::loadfile(const std::string& URL){
    startWidget->view->setRenderHint(QPainter::Antialiasing,true);
    std::pair<std::vector<Edges>,std::vector<Vertices>> mas = getMasVE(URL);
    std::vector<std::pair<int,int>> final;
    startWidget->scen->clear();
    addScengraph(mas);
}

//получение масива вершин и ребер для графа
std::pair<std::vector<Edges>,std::vector<Vertices>> EM_proj::getMasVE(const std::string& URL){
    Edges tmp =Edges();
    std::pair<std::vector<Edges>,std::vector<Vertices>> mas = tmp.get_ver_edges(URL);
    return mas;
}

//создание ребра по начальной ,конечной точке и выбор стиля ребра
QGraphicsLineItem* EM_proj::CreateItamEdges(const int& x1,const int& y1,
                                            const int& x2,const int& y2,
                                            const QPen& pen){
    QGraphicsLineItem* MyItem = new QGraphicsLineItem(x1,y1,x2,y2);
    MyItem->setPen(pen);
    return MyItem;
}

//создвние вершины по её координатам, выбор контура и заливки
QGraphicsEllipseItem* EM_proj::CreateItamVerties(const int& x,const int& y,
                                                 const int& r ,const QPen& pen,
                                                 const QBrush& brush){
    QGraphicsEllipseItem* MyItem = new QGraphicsEllipseItem(x,y,2*r,2*r);
    MyItem->setPen(pen);
    MyItem->setBrush(brush);
    return MyItem;
}
//добавление графа на сцену
void EM_proj::addScengraph(std::pair<std::vector<Edges>,std::vector<Vertices>>& mas){
    for (size_t i = 0; i < mas.first.size(); ++i) {
        QGraphicsLineItem* MyItem = CreateItamEdges(mas.first[i].get_x_from(),
                                                    mas.first[i].get_y_from(),
                                                    mas.first[i].get_x_to(),
                                                    mas.first[i].get_y_to(),
                                                    QPen(Qt::black,4,Qt::SolidLine));
        startWidget->scen->addItem(MyItem);
        //MyItem->setFlags(QGraphicsItem::ItemIsMovable); //возможная добавка перемещения ребра
    }
    for (size_t i = 0; i < mas.second.size(); ++i) {
        QGraphicsEllipseItem* MyItem = CreateItamVerties(mas.second[i].get_x()-15,
                                                         mas.second[i].get_y()-15,
                                                         15,
                                                         QPen(Qt::black,1,Qt::SolidLine),
                                                         QBrush(Qt::blue));
        startWidget->scen->addItem(MyItem);
        //MyItem->setFlags(QGraphicsItem::ItemIsMovable); //возможная добавка перемещения вершины
    }
};

//нахождения минимальных и максимальных точке на графе (чтобы потом его отцентровывать и масштабировать)
std::vector<std::pair<int,int>> EM_proj::findMinPointMaxPoint(
         std::pair<std::vector<Edges>,std::vector<Vertices>>& mas){
    std::vector<std::pair<int,int>> final;
    int max_x =  mas.second[0].get_x();
    int min_x =  mas.second[0].get_x();
    int max_y =  mas.second[0].get_y();
    int min_y =  mas.second[0].get_y();
    for (size_t i = 0; i < mas.second.size(); ++i) {
        if(mas.second[i].get_x()<=min_x){
            min_x =mas.second[i].get_x();
        }
        if(mas.second[i].get_y()<=min_y){
            min_y =mas.second[i].get_y();
        }
        if(mas.second[i].get_x()>=max_x){
            max_x =mas.second[i].get_x();
        }
        if(mas.second[i].get_y()>=max_y){
            max_y =mas.second[i].get_y();
        }
    }
    final.push_back(std::pair(min_x,max_x));
    final.push_back(std::pair(min_y,max_y));
    return final;
}

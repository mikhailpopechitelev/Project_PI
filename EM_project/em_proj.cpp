#include "em_proj.h"
#include "menu.h"
#include "startwidget.h"
#include "graph_parser.h"
#include <cstdlib>
//пока не сиользуемы люди для графа
//#include "human.h"
#include <thread>
#include <chrono>
#include <QList>
#include <QFileDialog>
#include <iostream>
#include <QtCore>
#include <QDebug>
#include <nlohmann_json/include/nlohmann/json.hpp>
#include <matplot/matplot.h>
QStackedWidget* EM_proj::getSteck(){
    return this->stack;
}

//создание конструктора
EM_proj::EM_proj(QWidget *parent)
    : QWidget{parent}
{
    startmenu = new Menu(this);
    startWidget = new StartWidget();
    authorsWidget = new Authors(this);

    //создание стка
    stack = new QStackedWidget();
    stack->addWidget(startmenu);


    //подключение кнопок приложения
    connect(startWidget->buttonBack,SIGNAL(clicked()),this,SLOT(slotButtonBack()));
    connect(startWidget->buttonChooseFile,SIGNAL(clicked()),this,SLOT(slotButtonChoose()));


    //создание расстановки
    QVBoxLayout* layout = new QVBoxLayout();

    //расстановка стека виджетов при создании проекта
    layout->addWidget(stack);
    this->setLayout(layout);
}

//методы заполнения стека и удаления из стека
void EM_proj::pushStack(QWidget* wgt){
    stack->addWidget(wgt);
}
void EM_proj::popStack(){
    stack->removeWidget(stack->currentWidget());
}

//реализация словот кнопок
void EM_proj::slotButtonBack(){
    stack->removeWidget(stack->currentWidget());
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
                                       "All Files (*.*);; GRAPH (*.graph);; TRIVIAL (*.tgf);");
    std::string URL = url.toStdString();
    if(URL != ""){
        loadfile(URL);
    }

}

//загрузка на сцену графа из файла
void EM_proj::loadfile(const std::string& URL){

    startWidget->view->setRenderHint(QPainter::Antialiasing,true);

    //создание векторов вершин, ребер и текста для дальнейшего заполнения
    std::vector<Vertices> m_ver; std::vector<Edges> m_edg;

    if(URL.substr(URL.find_last_of(".") + 1) == "graph") //определение расширения файла и парсинг файла *.graph
    {
        std::ifstream i(URL);
        nlohmann::json j;
        i>>j;
        //парсинг с помощью библиотеки nlohmann vertices,texts,edges
        nlohmann::json vertices  = j["vertices"];
        for(size_t i=0; i< vertices.size();i++){
            int x =vertices[i]["x"]; int y =vertices[i]["y"];std::string name =vertices[i]["name"];
            Vertices tmp = Vertices(x,y,name);
            m_ver.push_back(tmp);
        }
        nlohmann::json edges =j["edges"];
        for(size_t i=0; i< edges.size();i++){
            Vertices ver1 = Vertices(m_ver[edges[i]["vertex1"]]); Vertices ver2 =Vertices(m_ver[edges[i]["vertex2"]]);
            Edges tmp = Edges(ver1,ver2);
            m_edg.push_back(tmp);
        }
        startWidget->scen->clear();
    }else if(URL.substr(URL.find_last_of(".") + 1) == "tgf") // парсинг файла *.tgf
    {
        //разделяю файл сначало по '#' потом по '\n' потом по ' '

        std::vector<std::pair<size_t,size_t>> edges;      
        std::vector<std::string> edges_name;

        //заполнение ребер и нимен ребео по файлу tgf
        parseTgf(URL,edges_name,edges);
        auto g = matplot::graph(edges);

        //силовая расстановка графа
        g->layout_algorithm(matplot::network::layout::force);

        //получение коодринат вершин
        auto vec_x = g->x_data();
        auto vec_y = g->y_data();

        //заполнение масива вершин
        for (size_t i = 1; i < vec_x.size(); ++i) {
            qreal x =8*vec_x[i]; qreal y =8*vec_y[i];std::string name =edges_name[i-1];
            Vertices tmp = Vertices(x,y,name);
            //qDebug() << x <<" "<< y << " "<< QString::fromStdString(name);
            m_ver.push_back(tmp);
        }

        //заполнение массива ребер
        for (size_t i = 0; i < edges.size(); ++i) {
            Vertices ver1 = Vertices(m_ver[--(edges[i].first)]); Vertices ver2 =Vertices(m_ver[--(edges[i].second)]);
            Edges tmp = Edges(ver1,ver2);
            m_edg.push_back(tmp);
        }
    }

    //создание логического графа
    std::pair<std::vector<Edges>,std::vector<Vertices>> mas_tmp;
    mas_tmp.first = m_edg;
    mas_tmp.second = m_ver;

    //очистка старой сцены
    startWidget->scen->clear();

    //добавление нового графа на сцену
    addScengraph(mas_tmp);



    //создание сцены размером с левого до правого конца графа и с нижнего до верхнего
    std::vector<std::pair<int,int>> mas =findMinPointMaxPoint(mas_tmp);
    int len_x =mas[0].second-mas[0].first; int len_y = mas[1].second-mas[1].first; int min_x =mas[0].first; int min_y =mas[1].first;
    startWidget->scen->setSceneRect(min_x,min_y,len_x,len_y);

    //убираем старое представление
    startWidget->view->resetTransform();

    //скалирует изображение в зависимости от размеров окна
    qreal size_x = startWidget->view->width();; qreal size_y =startWidget->view->height();;
    qreal scale = std::min((size_x/len_x),(size_y/len_y));
    if(scale>=1){
        startWidget->view->scale(scale*0.8,scale*0.8);
    }else{
        scale =std::max((len_x/size_x)+1,(len_y/size_y)+1);
        startWidget->view->scale((1/scale),(1/scale));
    }

    startWidget->stepTimer->start(1000);
}

//создание ребра по начальной ,конечной точке и выбор стиля ребра
QGraphicsLineItem* EM_proj::CreateItamEdges(const int& x1,const int& y1,
                                            const int& x2,const int& y2,
                                            const QPen& pen){
    QGraphicsLineItem* MyItem = new QGraphicsLineItem(x1,y1,x2,y2);
    MyItem->setPen(pen);
    return MyItem;
}

MyQGraphicsRectItem* EM_proj::CreateMyItamVerties(const int& x,const int& y,const int& r,
                              const QPen& pen, const QBrush& brush){
MyQGraphicsRectItem* MyItem = new MyQGraphicsRectItem(x,y,r);
MyItem->setPen(pen);
MyItem->setBrush(brush);
return MyItem;
}

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


void EM_proj::parseTgf(const std::string &URL, std::vector<std::string>& edges_name, std::vector<std::pair<size_t,size_t>>& edges){
    std::ifstream file(URL);
    std::string str="";
    int i =0 ;
    while (std::getline(file, str, '#')) {
        if(i==0){
            std::stringstream Str(str);
            std::string str_tmp ="";
            while (std::getline(Str, str_tmp, '\n')) {
                std::stringstream Str_tmp(str_tmp);
                std::string str_t ="";
                int j = 0;
                while (std::getline(Str_tmp, str_t, ' ')) {
                    if(j==0){
                        //для названия вершин заполняю их имена
                        std::string name = str_t;
                        edges_name.push_back(name);
                    }
                    j++;
                }
            }
        }else if(i==1){
            for (size_t i = 0; i < str.size()-1; ++i) {
                str[i]=str[i+1];
            }
            str.pop_back();
            std::stringstream Str(str);
            std::string str_tmp ="";
            while (std::getline(Str, str_tmp, '\n')) {
                std::stringstream Str_tmp(str_tmp);
                std::string str_t ="";
                std::vector<size_t> vec_edge;
                while (std::getline(Str_tmp, str_t,' ')) {
                    //заполняю массив ребер
                    size_t edge = std::stoi(str_t);
                    vec_edge.push_back(edge);
                }
                edges.push_back(std::pair<int,int>(vec_edge[0],vec_edge[1]));
            }
        }
        i++;
    }
}

//добавление графа на сцену
void EM_proj::addScengraph(std::pair<std::vector<Edges>,std::vector<Vertices>>& mas){
    int font_size=this->startWidget->view->width()/200;
    for (size_t i = 0; i < mas.first.size(); ++i) {
        QGraphicsLineItem* MyItem = CreateItamEdges(mas.first[i].get_x_from(),
                                                    mas.first[i].get_y_from(),
                                                    mas.first[i].get_x_to(),
                                                    mas.first[i].get_y_to(),
                                                    QPen(Qt::black,font_size,Qt::SolidLine));
        startWidget->scen->addItem(MyItem);
        //MyItem->setFlags(QGraphicsItem::ItemIsMovable); //возможная добавка перемещения ребра
    }
    for (size_t i = 0; i < mas.second.size(); ++i) {
        if(mas.second[i].get_m_name()==""){
            MyQGraphicsRectItem* MyItem = CreateMyItamVerties(mas.second[i].get_x(),
                                                             mas.second[i].get_y(),this->startWidget->view->width()/70,
                                                             QPen(Qt::black,1,Qt::SolidLine),
                                                             QBrush(Qt::blue));
            startWidget->Vec_Item.push_back(MyItem);
            startWidget->scen->addItem(MyItem);
        }else{
            MyQGraphicsRectItem* MyItem = CreateMyItamVerties(mas.second[i].get_x(),
                                                             mas.second[i].get_y(),this->startWidget->view->width()/70,
                                                             QPen(Qt::black,1,Qt::SolidLine),
                                                             QBrush(Qt::blue));
            startWidget->Vec_Item.push_back(MyItem);
            startWidget->scen->addItem(MyItem);
        }
    }
};

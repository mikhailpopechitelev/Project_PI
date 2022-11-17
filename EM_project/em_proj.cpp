#include "em_proj.h"
#include "menu.h"
#include "startwidget.h"
#include "graph_parser.h"
#include "human.h"
#include <QFileDialog>
#include <iostream>
#include <QtCore>
#include <QDebug>
#include <nlohmann_json/include/nlohmann/json.hpp>

//создание конструктора
EM_proj::EM_proj(QWidget *parent)
    : QWidget{parent}
{
    //Заполнение стека
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
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
        loadfile(URL);
    }
}

//загрузка на сцену графа из файла
void EM_proj::loadfile(const std::string& URL){
    startWidget->view->setRenderHint(QPainter::Antialiasing,true);
    std::ifstream i(URL);
    nlohmann::json j;
    i>>j;
    std::vector<Vertices> m_ver; std::vector<Edges> m_edg; std::vector<Texts> m_tex;

    //парсинг с помощью библиотеки nlohmann vertices,texts,edges
    nlohmann::json vertices  = j["vertices"];
    for(size_t i=0; i< vertices.size();i++){
        int x =vertices[i]["x"]; int y =vertices[i]["y"];std::string name =vertices[i]["name"];
        Vertices tmp = Vertices(x,y,name);
        m_ver.push_back(tmp);
    }
    nlohmann::json text =j["texts"];
    for(size_t i=0; i< text.size();i++){
        if(text[i]["value"]!=""){
            int x = text[i]["x"]; int y =text[i]["y"]; std::string value = text[i]["value"];
            Texts tmp = Texts(x,y,value);
            m_tex.push_back(tmp);
        }
    }
    nlohmann::json edges =j["edges"];
    for(size_t i=0; i< edges.size();i++){
        Vertices ver1 = Vertices(m_ver[edges[i]["vertex1"]]); Vertices ver2 =Vertices(m_ver[edges[i]["vertex2"]]);
        Edges tmp = Edges(ver1,ver2);
        m_edg.push_back(tmp);
    }

    std::pair<std::vector<Edges>,std::vector<Vertices>> mas_tmp;
    mas_tmp.first = m_edg;
    mas_tmp.second = m_ver;

    //std::vector<std::pair<int,int>> final;
    startWidget->scen->clear();
    addScengraph(mas_tmp);
    int font_size=4;
    for (size_t i = 0; i < m_edg.size(); ++i) {
        QGraphicsLineItem* MyItem = CreateItamEdges(m_edg[i].get_x_from(),
                                                    m_edg[i].get_y_from(),
                                                    m_edg[i].get_x_to(),
                                                    m_edg[i].get_y_to(),
                                                    QPen(Qt::black,font_size,Qt::SolidLine));
        startWidget->scen->addItem(MyItem);
        //MyItem->setFlags(QGraphicsItem::ItemIsMovable); //возможная добавка перемещения ребра
    }
    int count_people =0;
    for (size_t i = 0; i < m_ver.size(); ++i) {
        if(m_ver[i].get_m_name()!=""){
            count_people+=std::stoi(m_ver[i].get_m_name());
        }else{
            count_people+=0;
        }
    }
    int sr_znach = count_people/m_ver.size();
    for (size_t i = 0; i < m_ver.size(); ++i) {
        if(m_ver[i].get_m_name()==""){
            MyQGraphicsRectItem* MyItem = CreateMyItamVerties(m_ver[i].get_x(),
                                                             m_ver[i].get_y(),0,sr_znach,
                                                             QPen(Qt::black,1,Qt::SolidLine),
                                                             QBrush(Qt::blue));
            startWidget->scen->addItem(MyItem);
        }else{
            MyQGraphicsRectItem* MyItem = CreateMyItamVerties(m_ver[i].get_x(),
                                                             m_ver[i].get_y(),std::stoi(m_ver[i].get_m_name()),sr_znach,
                                                             QPen(Qt::black,1,Qt::SolidLine),
                                                             QBrush(Qt::blue));
            startWidget->scen->addItem(MyItem);
        }
        //startWidget->scen->add
        //Human* hum = new Human(mas.second[i].get_x()-10,mas.second[i].get_y()-10);
        //startWidget->scen->addSimpleText();
        //MyItem->setFlags(QGraphicsItem::ItemIsMovable); //возможная добавка перемещения вершины
    }
    /*
    for (size_t i = 0; i < m_tex.size(); ++i) {
        QGraphicsSimpleTextItem text =QGraphicsSimpleTextItem(QString::fromStdString(m_tex[i].get_text()));
        text.setPos(m_tex[i].get_x(),m_tex[i].get_y());
        startWidget->scen->addItem(&text);
        //std::cout << m_tex[i].get_text();
    }
    */



    //создание сцены размером с левого до правого конца графа и с нижнего до верхнего
    std::vector<std::pair<int,int>> mas =findMinPointMaxPoint(mas_tmp);
    int len_x =mas[0].second-mas[0].first; int len_y = mas[1].second-mas[1].first; int min_x =mas[0].first; int min_y =mas[1].first;
    startWidget->scen->setSceneRect(min_x,min_y,len_x,len_y);

    //убираем старое представление
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

//создание ребра по начальной ,конечной точке и выбор стиля ребра
QGraphicsLineItem* EM_proj::CreateItamEdges(const int& x1,const int& y1,
                                            const int& x2,const int& y2,
                                            const QPen& pen){
    QGraphicsLineItem* MyItem = new QGraphicsLineItem(x1,y1,x2,y2);
    MyItem->setPen(pen);
    return MyItem;
}

//добавление графа на сцену
void EM_proj::addScengraph(std::pair<std::vector<Edges>,std::vector<Vertices>>& mas){

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

MyQGraphicsRectItem* EM_proj::CreateMyItamVerties(const int& x,const int& y,const int& wight,const int& all_v,
                              const QPen& pen, const QBrush& brush){
MyQGraphicsRectItem* MyItem = new MyQGraphicsRectItem(x,y,wight,all_v);
MyItem->setPen(pen);
MyItem->setBrush(brush);
return MyItem;
}

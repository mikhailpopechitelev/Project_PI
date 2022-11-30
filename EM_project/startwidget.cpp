#include <startwidget.h>


StartWidget::StartWidget(QWidget *parent)
    : QWidget{parent}
{
    //инициализируем поля
    buttonBack = new QPushButton("Back");
    buttonStart = new QPushButton("Start");
    buttonChooseFile = new QPushButton("Choose file");
    scen = new QGraphicsScene(QRectF(-500,-500,1000,1000));
    view = new MyGraphicsView(scen);

    //подключение кнопок приложения
    connect(buttonBack,SIGNAL(clicked()),parent,SLOT(slotButtonBack()));
    connect(buttonChooseFile,SIGNAL(clicked()),this,SLOT(slotButtonChoose()));

    //создание расположения кнопок
    QHBoxLayout* HBoxLayout = new QHBoxLayout();
    QVBoxLayout* VBoxLayoutfirst = new QVBoxLayout();
    QVBoxLayout* VBoxLayoutsecond = new QVBoxLayout();
    QPushButton* push = new QPushButton("s");

    //создание таймера для кадров в секунду и шага заражения
    animatiomTimer = new QTimer(this);
    stepTimer = new QTimer(this);

    //подключение сигналов для StartWidget
    connect(animatiomTimer,SIGNAL(timeout()),scen,SLOT(advance()));
    connect(stepTimer,SIGNAL(timeout()),this,SLOT(onStepTimer()));

    //старк таймера
    //animatiomTimer->start(1000/24);

    //вертикальная расстановка
    VBoxLayoutfirst->addWidget(buttonStart);
    VBoxLayoutfirst->addWidget(buttonChooseFile);
    VBoxLayoutfirst->addWidget(buttonBack);

    //расстановка слева на право
    HBoxLayout->addLayout(VBoxLayoutfirst);

    //добавлене в центр виджета
    HBoxLayout->addWidget(view);

    //добавление левой расстановки
    VBoxLayoutsecond->addWidget(push);
    HBoxLayout->addLayout(VBoxLayoutsecond);

    this->setLayout(HBoxLayout);
}

//слот выбора файла через диалоговое окно
void StartWidget::slotButtonChoose(){
    //получает ссылку на файл и приводит её к типу строки
    QString url;
    url = QFileDialog::getOpenFileName(this,"Выбрать файл","C:\\",
                                       "All Files (*.*);; GRAPH (*.graph);; TRIVIAL (*.tgf);");
    std::string URL = url.toStdString();
    if(URL != ""){
        loadfile(URL);
    }
}

void StartWidget::onStepTimer(){
    Vec_Item[rand()%(Vec_Item.size())]->sick();
}


//загрузка на сцену графа из файла
void StartWidget::loadfile(const std::string& URL){

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
        scen->clear();
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
            qDebug() << x <<" "<< y << " "<< QString::fromStdString(name);
            m_ver.push_back(tmp);
        }
        qDebug() << 4;
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
    scen->clear();

    //добавление нового графа на сцену
    addScengraph(mas_tmp);

    //создание сцены размером с левого до правого конца графа и с нижнего до верхнего
    std::vector<std::pair<int,int>> mas =findMinPointMaxPoint(mas_tmp);
    int len_x =mas[0].second-mas[0].first; int len_y = mas[1].second-mas[1].first; int min_x =mas[0].first; int min_y =mas[1].first;
    scen->setSceneRect(min_x,min_y,len_x,len_y);

    //убираем старое представление
    view->resetTransform();

    //скалирует изображение в зависимости от размеров окна
    qreal size_x = view->width();
    qreal size_y =view->height();
    qreal scale = std::min((size_x/len_x),(size_y/len_y));
    if(scale>=1){
        view->scale(scale*0.8,scale*0.8);
    }else{
        scale =std::max((len_x/size_x)+1,(len_y/size_y)+1);
        view->scale((1/scale),(1/scale));
    }
    qDebug() << 5;

    stepTimer->start(1000);
}

//создание ребра по начальной ,конечной точке и выбор стиля ребра
QGraphicsLineItem* StartWidget::CreateItamEdges(const int& x1,const int& y1,
                                            const int& x2,const int& y2,
                                            const QPen& pen){
    QGraphicsLineItem* MyItem = new QGraphicsLineItem(x1,y1,x2,y2);
    MyItem->setPen(pen);
    return MyItem;
}

MyQGraphicsRectItem* StartWidget::CreateMyItamVerties(const int& x,const int& y,const int& r,
                              const QPen& pen, const QBrush& brush){
MyQGraphicsRectItem* MyItem = new MyQGraphicsRectItem(x,y,r);
MyItem->setPen(pen);
MyItem->setBrush(brush);
return MyItem;
}

//нахождения минимальных и максимальных точке на графе (чтобы потом его отцентровывать и масштабировать)
std::vector<std::pair<int,int>> StartWidget::findMinPointMaxPoint(
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


void StartWidget::parseTgf(const std::string &URL, std::vector<std::string>& edges_name, std::vector<std::pair<size_t,size_t>>& edges){
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
void StartWidget::addScengraph(std::pair<std::vector<Edges>,std::vector<Vertices>>& mas){
    int font_size=view->width()/200;
    for (int var = 0; var < mas.second.size(); ++var) {
        qDebug() << mas.second[var].get_x() <<mas.second[var].get_y();
    }
    for (size_t i = 0; i < mas.first.size(); ++i) {
        QGraphicsLineItem* MyItem = CreateItamEdges(mas.first[i].get_x_from(),
                                                    mas.first[i].get_y_from(),
                                                    mas.first[i].get_x_to(),
                                                    mas.first[i].get_y_to(),
                                                    QPen(Qt::black,font_size,Qt::SolidLine));
        scen->addItem(MyItem);
        //MyItem->setFlags(QGraphicsItem::ItemIsMovable); //возможная добавка перемещения ребра
    }
    for (size_t i = 0; i < mas.second.size(); ++i) {
        if(mas.second[i].get_m_name()==""){
            MyQGraphicsRectItem* MyItem = CreateMyItamVerties(mas.second[i].get_x(),
                                                             mas.second[i].get_y(),view->width()/70,
                                                             QPen(Qt::black,1,Qt::SolidLine),
                                                             QBrush(Qt::blue));
            Vec_Item.push_back(MyItem);
            scen->addItem(MyItem);
        }else{
            MyQGraphicsRectItem* MyItem = CreateMyItamVerties(mas.second[i].get_x(),
                                                             mas.second[i].get_y(),view->width()/70,
                                                             QPen(Qt::black,1,Qt::SolidLine),
                                                             QBrush(Qt::blue));
            Vec_Item.push_back(MyItem);
            scen->addItem(MyItem);
        }
    }
};



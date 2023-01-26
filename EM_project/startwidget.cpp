#include <startwidget.h>

StartWidget::StartWidget(QWidget *parent)
    : QWidget{parent}
{
    //создание выдвигающихся списков
    Boxlayout = new QComboBox();
    QStringList lst;
    lst << "dot" << "fdp" << "neato" << "osage"<< "sfdp" << "twopi";
    Boxlayout->addItems(lst);
    lst.clear();

    BoxStepQuarantine = new QComboBox();
    lst << "Масочный режим" << "Частичная изоляция" << "Двухнедельный карантин" << "Полная изоляция";
    BoxStepQuarantine->addItems(lst);

    //создание галочки для карантина
    quarantine = new QCheckBox("Карантин");

    //инициализируем поля
    buttonBack = new QPushButton("Назад");
    buttonStart = new QPushButton("Начать");
    buttonRepeat = new QPushButton("Повторить");

    //заполнение надписей для стартового окна
    QLabel* chance_sick_lbl = new QLabel("Шанс заболеть"); ;
    QLabel* mortality_rate_lbl= new QLabel("Коэффициент летальности");
    QLabel* distribution_lbl= new QLabel("Коэффициент распространения");
    QLabel* health_efficiency_lbl = new QLabel("Эффективность здравоохранения");
    countDay = new QLabel("0");

    //создание счетчика от скольки процентов зараженных будет введет карантин
    quarantinePros = new QSpinBox(this);
    quarantinePros->setRange(0,100);
    quarantinePros->setValue(35);
    quarantinePros->setPrefix("Карантин: ");
    quarantinePros->setSuffix("%");
    quarantinePros->setButtonSymbols(QSpinBox::PlusMinus);
    quarantinePros->setWrapping(true);

    //создание счетчика от скольки процентов зараженных будет введет карантин
    BoxstepTimer = new QSpinBox(this);
    BoxstepTimer->setRange(0,3000);
    BoxstepTimer->setValue(200);
    BoxstepTimer->setSingleStep(100);
    BoxstepTimer->setSuffix("мс");
    BoxstepTimer->setButtonSymbols(QSpinBox::PlusMinus);
    BoxstepTimer->setWrapping(true);

    //создание счетчика дней болезни
    sickDays = new QSpinBox(this);
    sickDays->setRange(0,14);
    sickDays->setValue(1);
    sickDays->setPrefix("Дни болезни: ");
    sickDays->setButtonSymbols(QSpinBox::PlusMinus);
    sickDays->setWrapping(true);

    //создание счетчика инкубационный период
    dayToRecover = new QSpinBox(this);
    dayToRecover->setRange(0,21);
    dayToRecover->setValue(1);
    dayToRecover->setPrefix("Инкубационный период: ");
    dayToRecover->setButtonSymbols(QSpinBox::PlusMinus);
    dayToRecover->setWrapping(true);

    //создание счетчика для дней до потери имунитета
    dayToUnrecover = new QSpinBox(this);
    dayToUnrecover->setRange(0,365);
    dayToUnrecover->setValue(1);
    dayToUnrecover->setPrefix("Дней до потери иммунитета: ");
    dayToUnrecover->setButtonSymbols(QSpinBox::PlusMinus);
    dayToUnrecover->setWrapping(true);

    //ползунок коэффициента распространения
    distribution_с = new QSlider(Qt::Horizontal);
    distribution_с->setRange(0,10);
    distribution_с->setTickInterval(1);
    distribution_с->setValue(0);
    distribution_с->setTickPosition(QSlider::TicksBelow);

    //ползунок шанса заболеть
    chance_sick = new QSlider(Qt::Horizontal);
    chance_sick->setRange(0,10);
    chance_sick->setTickInterval(1);
    chance_sick->setValue(0);
    chance_sick->setTickPosition(QSlider::TicksBelow);

    //коэффициент летальности
    mortality_rate = new QSlider(Qt::Horizontal);
    mortality_rate->setRange(0,10);
    mortality_rate->setTickInterval(1);
    mortality_rate->setValue(0);
    mortality_rate->setTickPosition(QSlider::TicksBelow);

    //коэйффициент эффективности здравоохранения
    health_efficiency = new QSlider(Qt::Horizontal);
    health_efficiency->setRange(0,10);
    health_efficiency->setTickInterval(1);
    health_efficiency->setValue(0);
    health_efficiency->setTickPosition(QSlider::TicksBelow);

    buttonChooseFile = new QPushButton("Выбрать файл");
    scen = new QGraphicsScene(QRectF(-500,-500,1000,1000));
    view = new MyGraphicsView(scen);
    m_sick = 0;

    //подключение кнопок приложения
    connect(buttonBack,SIGNAL(clicked()),parent,SLOT(slotButtonBack()));
    connect(buttonChooseFile,SIGNAL(clicked()),this,SLOT(slotButtonChoose()));
    connect(buttonStart,SIGNAL(clicked()),this,SLOT(onStartButton()));
    connect(buttonRepeat,SIGNAL(clicked()),this,SLOT(onButtonRepeat()));
    connect(distribution_с,SIGNAL(valueChanged(int)),this,SLOT(onSliderdistribution()));
    connect(health_efficiency,SIGNAL(valueChanged(int)),this,SLOT(onSliderHealthEfficiency()));
    connect(mortality_rate,SIGNAL(valueChanged(int)),this,SLOT(onSliderMortalityRate()));
    connect(chance_sick,SIGNAL(valueChanged(int)),this,SLOT(onChanceSick()));
    connect(BoxstepTimer,SIGNAL(valueChanged(int)),this,SLOT(ChangeTimer(int)));

    //создание расположения кнопок
    QHBoxLayout* HBoxLayout = new QHBoxLayout();
    QVBoxLayout* VBoxLayoutfirst = new QVBoxLayout();
    QVBoxLayout* VBoxLayoutsecond = new QVBoxLayout();

    //создание таймера для кадров в секунду и шага заражения
    animatiomTimer = new QTimer(this);
    stepTimer = new QTimer(this);

    //подключение сигналов для StartWidget
    connect(animatiomTimer,SIGNAL(timeout()),scen,SLOT(advance()));
    connect(stepTimer,SIGNAL(timeout()),this,SLOT(onStepTimer()));

    //вертикальная расстановка
    VBoxLayoutfirst->addWidget(buttonStart);
    VBoxLayoutfirst->addWidget(buttonRepeat);
    VBoxLayoutfirst->addWidget(distribution_lbl);
    VBoxLayoutfirst->addWidget(distribution_с);
    VBoxLayoutfirst->addWidget(chance_sick_lbl);
    VBoxLayoutfirst->addWidget(chance_sick);
    VBoxLayoutfirst->addWidget(mortality_rate_lbl);
    VBoxLayoutfirst->addWidget(mortality_rate);
    VBoxLayoutfirst->addWidget(health_efficiency_lbl);
    VBoxLayoutfirst->addWidget(health_efficiency);
    VBoxLayoutfirst->addWidget(sickDays);
    VBoxLayoutfirst->addWidget(dayToRecover);
    VBoxLayoutfirst->addWidget(dayToUnrecover);
    VBoxLayoutfirst->addWidget(quarantinePros);
    VBoxLayoutfirst->addWidget(buttonChooseFile);
    VBoxLayoutfirst->addWidget(buttonBack);

    //расстановка слева на право
    HBoxLayout->addLayout(VBoxLayoutfirst);

    //добавлене в центр виджета
    HBoxLayout->addWidget(view);

    //добавление левой расстановки
    VBoxLayoutsecond->addWidget(BoxstepTimer);
    VBoxLayoutsecond->addWidget(countDay);
    VBoxLayoutsecond->addWidget(Boxlayout);
    VBoxLayoutsecond->addWidget(BoxStepQuarantine);
    VBoxLayoutsecond->addWidget(quarantine);
    HBoxLayout->addLayout(VBoxLayoutsecond);

    this->setLayout(HBoxLayout);
}

//слот выбора файла через диалоговое окно
void StartWidget::slotButtonChoose(){
    //получает ссылку на файл и приводит её к типу строки
    QString url;
    url = QFileDialog::getOpenFileName(this,"Выбрать файл","C:\\",
                                       "GRAPH (*.graph);; DOT (*.dot);; TXT (*.txt);");

    std::string URL = url.toStdString();
    if(URL != ""){
        this->URL = URL;
        if(buttonStart->text()!="Начать"){
            buttonStart->setText("Начать");
        }
        Vec_Item.clear();
        adjacency_list.clear();
        loadfile(URL);
        Vec_Item[0]->infected();
        stepTimer->stop();
    }
}

void StartWidget::onStepTimer(){

    daySimulation++;
    countDay->setNum(daySimulation);
    //количество зараженных
    std::vector<int> tmp;

    //подсчет количество зараженных вершин
    for (size_t i = 0; i < Vec_Item.size(); ++i) {
        if((Vec_Item[i]->isSick())||(Vec_Item[i]->isInfectd())){
            tmp.push_back(i);
        }
    }

    //заражение всех соседних клеток для вершины
    for (size_t i = 0; i < tmp.size(); ++i) {
        for (size_t j = 0; j < adjacency_list[tmp[i]].size(); ++j) {
            if((!adjacency_list[tmp[i]][j]->isRecover())&&(!adjacency_list[tmp[i]][j]->isDead())){
                int k = 10;
                if(quarantine->isChecked()){
                    if(((tmp.size()*100)/Vec_Item.size())>=quarantinePros->value()){
                        if(BoxStepQuarantine->currentText()=="Масочный режим"){// "Mask mode" << "partial isolation" << "two-week quarantine" << "complete isolation"
                            k=8;
                        }else if(BoxStepQuarantine->currentText()=="Частичная изоляция"){
                            k=6;
                        }else if(BoxStepQuarantine->currentText()=="Двухнедельный карантин"){
                            k=4;
                        }else if(BoxStepQuarantine->currentText()=="Полная изоляция"){
                            k=1;
                        }
                        if(rand()%100 < m_distribution_с*k){ //коэффициент распространения поменять на константу
                            adjacency_list[tmp[i]][j]->infected(); //sick
                        }
                    }else{
                        if(rand()%10 < m_distribution_с){ //коэффициент распространения поменять на константу
                            adjacency_list[tmp[i]][j]->infected(); //sick
                        }
                    }
                }else{
                    if(rand()%10 < m_distribution_с){ //коэффициент распространения поменять на константу
                        adjacency_list[tmp[i]][j]->infected(); //sick
                    }
                }

            }
        }
    }
    //для каждой верины подсчет количества её дней болезни
    for (size_t i = 0; i < Vec_Item.size(); ++i) {
        if((Vec_Item[i]->isInfectd())&&(!Vec_Item[i]->isSick())){
            Vec_Item[i]->day_sick++;
            if(Vec_Item[i]->day_sick==dayToRecover->value()){
                if((rand()%10 < m_chance_sick)){//шанс заболеть
                    Vec_Item[i]->sick();
                }else{
                    Vec_Item[i]->recover();
                    Vec_Item[i]->day_sick=0;
                }
            }
        }
        if(Vec_Item[i]->isSick()){
            Vec_Item[i]->day_sick++;
            if(Vec_Item[i]->day_sick==dayToRecover->value()+sickDays->value()){// 8 - 3 количество дней для выздоровления
                if(rand()%10 < m_mortality_rate){//коэффициент мсертности
                    Vec_Item[i]->dead();
                    Vec_Item[i]->day_sick=0;
                    countDead++;
                }else{
                    Vec_Item[i]->recover();
                    Vec_Item[i]->day_sick=0;
                }
            }
        }
        if(Vec_Item[i]->isRecover()){
            Vec_Item[i]->day_recovered++;
            if(Vec_Item[i]->day_recovered==dayToUnrecover->value()){
                Vec_Item[i]->unrecovered();
                Vec_Item[i]->day_recovered=0;
            }
        }
    }
    int count_sick=0;
    for (size_t i = 0; i < Vec_Item.size(); ++i) {
        if((Vec_Item[i]->isSick())||(Vec_Item[i]->isInfectd())){
            count_sick++;
        }
    }
    if(count_sick==0){
        this->stepTimer->stop();
    }
    scen->update();
}

std::string readFile(const std::string& fileName) {
    std::ifstream f(fileName);
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
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
            Vertices tmp = Vertices(x,y,name,i);
            m_ver.push_back(tmp);
        }
        nlohmann::json edges =j["edges"];
        for(size_t i=0; i< edges.size();i++){
            Vertices ver1 = Vertices(m_ver[edges[i]["vertex1"]]); Vertices ver2 =Vertices(m_ver[edges[i]["vertex2"]]);
            Edges tmp = Edges(ver1,ver2);
            m_edg.push_back(tmp);
        }
        scen->clear();
    }/*else if(URL.substr(URL.find_last_of(".") + 1) == "tgf") // парсинг файла *.tgf
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
    }*/
    else if(URL.substr(URL.find_last_of(".") + 1) == "txt") // парсинг файла c языком .DOT
        {
            GVC_t* gvc;
            Agraph_t* G;
            gvc = gvContext();
            std::string s;
            std::ifstream f(URL);
            std::stringstream ss;
            ss << f.rdbuf();
            s = ss.str();
            QString qstr = QString::fromStdString(s);
            G = agmemread(s.c_str());

            //расположение графа
            QString tmpQ = Boxlayout->currentText();
            const char* tmp = tmpQ.toStdString().c_str();
            gvLayout(gvc, G, tmp); // dot fdp neato nop nop1 nop2 osage patchwork sfdp twopi

            //создание узлов и ребер
            Agnode_t* n;
            Agedge_t* e;
            int id = 0;

            //перебор всех узлов и сопоставление кажому свой id создание массива вершин m_ver
            for (n = agfstnode(G); n; n = agnxtnode(G,n)) {
                std::string s = std::to_string(id);
                const char* str = s.c_str();
                Agsym_t *attr_label = agattr(G, AGNODE, "id", "");
                agset(n,"id",str);
                Vertices tmpnode = Vertices(ND_coord(n).x,ND_coord(n).y,agnameof(n),id); //((Agnodeinfo_t*)AGDATA(n))->id) ;
                m_ver.push_back(tmpnode);
                id++;
            }

            //обход всех ребер и заполнение массива ребер m_edg
            Agnode_t* n_;
            int count =0;
            for (n_ = agfstnode(G); n_; n_ = agnxtnode(G,n_)) {
                for (e = agfstout(G,n_); e; e = agnxtout(G,e)){
                    Vertices ver1 = Vertices(ND_coord(agtail(e)).x,ND_coord(agtail(e)).y,
                                             agnameof(agtail(e)),std::stoi(agget(agtail(e),"id")));
                    Vertices ver2 =Vertices(ND_coord(aghead(e)).x,ND_coord(aghead(e)).y,
                                            agnameof(aghead(e)),std::stoi(agget(aghead(e),"id")));
                    //qDebug() << ver1.get_id() << ver2.get_id();
                    Edges tmp = Edges(ver1,ver2);
                    m_edg.push_back(tmp);
                    count++;
                }
            }

            //очиста ресурсов компьютера
            gvFreeLayout(gvc, G);
            agclose(G);
            gvFreeContext(gvc);
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
}


//создание ребра по начальной ,конечной точке и выбор стиля ребра
QGraphicsLineItem* StartWidget::CreateItamEdges(const int& x1,const int& y1,
                                            const int& x2,const int& y2,
                                            const QPen& pen){
    QGraphicsLineItem* MyItem = new QGraphicsLineItem(x1,y1,x2,y2);
    MyItem->setPen(pen);
    return MyItem;
}

MyQGraphicsRectItem* StartWidget::CreateMyItamVerties(const int& x,const int& y,const qreal& r,
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
    //qreal font_size = 0.75/3;
    //создание всех ребер

    for (size_t i = 0; i < mas.first.size(); ++i) {
        QGraphicsLineItem* MyItem = CreateItamEdges(mas.first[i].get_vertices_from().get_x(),
                                                    mas.first[i].get_vertices_from().get_y(),
                                                    mas.first[i].get_vertices_to().get_x(),
                                                    mas.first[i].get_vertices_to().get_y(),
                                                    QPen(Qt::gray,font_size,Qt::SolidLine));
        scen->addItem(MyItem);
        //MyItem->setFlags(QGraphicsItem::ItemIsMovable); //возможная добавка перемещения ребра
    }

    //создание логического списка смежности
    std::vector<std::vector<Vertices>> tmp;
    tmp.resize(mas.second.size());
    adjacency_list.resize(mas.second.size());
    for (size_t i = 0; i < mas.first.size(); ++i) {
        tmp[mas.first[i].get_vertices_from().get_id()].push_back(mas.first[i].get_vertices_to());
        tmp[mas.first[i].get_vertices_to().get_id()].push_back(mas.first[i].get_vertices_from());
    }

    adjacency_list.resize(mas.second.size());
    Vec_Item.resize(mas.second.size());
    //создание узлов графа и заполнение списка смежности
    //можно было заолнить список через itamAt но он возвращает QGraphicsItem* из-за чего вызвать sick() нельзя
    for (size_t i = 0; i < mas.second.size(); ++i) {
        if(mas.second[i].get_m_name()==""){
            MyQGraphicsRectItem* MyItem = CreateMyItamVerties(mas.second[i].get_x(),
                                                             mas.second[i].get_y(),view->width()/70,//view->width()/70,std::sqrt((scen->width()*scen->height())/(75*Vec_Item.size()))
                                                             QPen(Qt::gray,1,Qt::SolidLine),
                                                             QBrush(Qt::blue));
            Vec_Item[i]=(MyItem);
            scen->addItem(MyItem);
            for (size_t j = 0; j < tmp.size(); ++j) {
                for (size_t k = 0; k < tmp[j].size(); ++k) {
                    if(tmp[j][k].get_id()==mas.second[i].get_id()){
                        adjacency_list[j].push_back(MyItem);
                    }
                }
            }            
        }else{
            MyQGraphicsRectItem* MyItem = CreateMyItamVerties(mas.second[i].get_x(),
                                                             mas.second[i].get_y(),view->width()/70,//view->width()/70,std::sqrt((scen->width()*scen->height())/(75*Vec_Item.size()))
                                                             QPen(Qt::gray,1,Qt::SolidLine),
                                                             QBrush(Qt::blue));
            Vec_Item[i]=(MyItem);
            scen->addItem(MyItem);
            for (size_t j = 0; j < tmp.size(); ++j) {
                for (size_t k = 0; k < tmp[j].size(); ++k) {
                    if(tmp[j][k].get_id()==mas.second[i].get_id()){
                        adjacency_list[j].push_back(MyItem);
                    }
                }
            }
        }
    }
    /*
    for (int var = 0; var < adjacency_list.size(); ++var) {
        for (int j = 0; j < adjacency_list[var].size(); ++j) {
            adjacency_list[var][j]->print_id();
        }
    }*/
    /*
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
    }*/
};

void StartWidget::onStartButton(){
    if(URL!=""){
        if((buttonStart->text()=="Начаит")||(buttonStart->text()=="Продолжить")){
            buttonStart->setText("Остановить");
            scen->update();
            stepTimer->start(BoxstepTimer->value());
        }else{
            buttonStart->setText("Продолжить");
            stepTimer->stop();
        }
    }
}

void StartWidget::onSliderdistribution(){
    this->m_distribution_с = distribution_с->sliderPosition();
}

void StartWidget::onSliderHealthEfficiency(){
    this->m_health_efficiency = health_efficiency->sliderPosition();
}

void StartWidget::onSliderMortalityRate(){
    this->m_mortality_rate = mortality_rate->sliderPosition();
}

void StartWidget::onChanceSick(){
    this->m_chance_sick = chance_sick->sliderPosition();
}

void StartWidget::onButtonRepeat(){
    if(URL!=""){
        if(buttonStart->text()!="Начать"){
            buttonStart->setText("Начать");
        }
        Vec_Item.clear();
        adjacency_list.clear();
        loadfile(URL);
        Vec_Item[0]->infected();
        stepTimer->stop();
        countDay->setNum(0);
        daySimulation = 0;
    }
}

void StartWidget::ChangeTimer(int step){
    stepTimer->setInterval(step);
}

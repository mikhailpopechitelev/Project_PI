#ifndef STARTWIDGET_H
#define STARTWIDGET_H
#include <graph_parser.h>
#include <myqgraphicsrectiten.h>
#include <QFileDialog>
#include <mygraphicsview.h>
#include <QPushButton>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLayout>
#include <QStackedWidget>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <nlohmann_json/include/nlohmann/json.hpp>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QMenu>
#include <QComboBox>

//#include <matplot/matplot.h>
#include<gvc.h>




class StartWidget: public QWidget
{
    Q_OBJECT
public:

    explicit StartWidget(QWidget *parent = nullptr);

public:

    void sendButtonQuite();

    //загрузка файла и его парсер через *.graph и *.tgf
    void loadfile(const std::string& url);

    //работа с графами считанными из файла
    void parseTgf(const std::string& url,std::vector<std::string>& edges_name,
                  std::vector<std::pair<size_t,size_t>>& edges);

    //отрисовка графа по списку вершин и ребер
    void addScengraph(std::pair<std::vector<Edges>,std::vector<Vertices>>& mas);

    //нахождение крайних точек для графа, чтобы изменить рзамер сцены и поставить его по середине
    std::vector<std::pair<int,int>> findMinPointMaxPoint(
              std::pair<std::vector<Edges>,std::vector<Vertices>>& mas);

    //методы создания вершин и ребер
    //QGraphicsRectItem* CreateItamRectverties(const int& x,const int& y,const int& r,const QPen& pen, const QBrush& brush);
    QGraphicsLineItem* CreateItamEdges(const int& x1,const int& y1,
                                   const int& x2,const int& y2,
                                   const QPen& pen);
    MyQGraphicsRectItem* CreateMyItamVerties(const int& x,const int& y,const qreal& r,
                                             const QPen& pen, const QBrush& brush);
    std::string readFile(const std::string& str);
signals:
    void signalFromButton(QString str);

public slots:

    void slotButtonChoose();
    void onButtonRepeat();
    void onStepTimer();
    void onStartButton();
    void onSliderdistribution();
    void onSliderMortalityRate();
    void onSliderHealthEfficiency();
    void onChanceSick();
    void ChangeTimer(int);

private:

    int countDead=0;
    int daySimulation = 0;
    QLabel* countDay = nullptr;
    QComboBox* BoxStepQuarantine = nullptr;
    QComboBox* Boxlayout=nullptr;
    QSpinBox* BoxstepTimer = nullptr;
    QCheckBox* quarantine = nullptr;
    QSpinBox* sickDays= nullptr;
    QSpinBox* dayToRecover= nullptr;
    QSpinBox* quarantinePros= nullptr;
    QSpinBox* dayToUnrecover= nullptr;
    QSlider* chance_sick= nullptr;
    QSlider* mortality_rate= nullptr;
    QSlider* health_efficiency= nullptr;
    QSlider* distribution_с= nullptr;
    std::vector<MyQGraphicsRectItem*> Vec_Item;
    //std::vector<QGraphicsLineItem*> Vec_Imem_edges;
    std::vector<std::vector<MyQGraphicsRectItem*>> adjacency_list;
    QTimer* stepTimer= nullptr;
    QGraphicsScene* scen= nullptr;
    MyGraphicsView* view= nullptr;
    QPushButton* buttonRepeat= nullptr;
    QPushButton* buttonBack= nullptr;
    QPushButton* buttonStart= nullptr;
    QPushButton* buttonChooseFile= nullptr;
    QTimer* animatiomTimer= nullptr;
    int m_chance_sick=0;
    int m_sick=0;
    int m_mortality_rate=0;
    int m_health_efficiency=0;
    int m_distribution_с=0;
    std::string URL= "";

};

#endif // STARTWIDGET_H

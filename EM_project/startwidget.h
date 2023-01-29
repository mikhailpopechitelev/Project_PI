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
#include <Graphviz/include/graphviz/gvc.h>
//#include <gvc.h>




/**
*  @brief класс окна в котором настраивается симуляция
*/
class StartWidget: public QWidget
{
    Q_OBJECT
public:

    explicit StartWidget(QWidget *parent = nullptr);

public:

    void sendButtonQuite();

    /**
    *  @brief функция загрузки файла в программу (память)
    *  @param url ссылка на логический граф
    */
    void loadfile(const std::string& url);
    void parseTgf(const std::string& url,std::vector<std::string>& edges_name,
                  std::vector<std::pair<size_t,size_t>>& edges);

    /**
    *  @brief функция отрисовывающая граф на сцене
    *  @param mas список вершин и ребер
    */
    void addScengraph(std::pair<std::vector<Edges>,std::vector<Vertices>>& mas);

    //!нахождение крайних точек для графа, чтобы изменить рзамер сцены и поставить его по середине
    std::vector<std::pair<int,int>> findMinPointMaxPoint(
              std::pair<std::vector<Edges>,std::vector<Vertices>>& mas);

    //методы создания вершин и ребер
    //QGraphicsRectItem* CreateItamRectverties(const int& x,const int& y,const int& r,const QPen& pen, const QBrush& brush);
    /**
    *  @brief конструктор ребра
    *  @param x1 координата x начала
    *  @param x2 координата x конца
    *  @param y1 координата y начала
    *  @param y2 координата y конца
    *  @param pen стиль каисточки для отрисовки
    *  @return ребро
    */
    QGraphicsLineItem* CreateItamEdges(const int& x1,const int& y1,
                                   const int& x2,const int& y2,
                                   const QPen& pen);
    /**
    *  @brief конструктор узла
    *  @param x координата x центра узла
    *  @param y координата y центра узла
    *  @param r радиус узла
    *  @param brush кисть для заливки
    *  @param pen стиль каисточки для отрисовки
    *  @return ребро
    */
    MyQGraphicsRectItem* CreateMyItamVerties(const int& x,const int& y,const qreal& r,
                                             const QPen& pen, const QBrush& brush);
    std::string readFile(const std::string& str);
signals:
    //!сигнал отсылающийся при нажатии на кнопку
    void signalFromButton(QString str);

public slots:

    //! слот кнопки выбора файла
    void slotButtonChoose();
    //! слот кнопки повтора
    void onButtonRepeat();
    //! слот кнопки шага таймера
    void onStepTimer();
    //! слот кнопки старта
    void onStartButton();
    //! слот прокрутки ползунков
    void onSliderdistribution();
    void onSliderMortalityRate();
    void onSliderHealthEfficiency();
    //! слот шанса заболеть в такт таймера
    void onChanceSick();
    //! слот начала таймера
    void ChangeTimer(int);

private:

    //!поля стартовой настройки симуляции
    ///\code
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
    ///\endcode
};

#endif // STARTWIDGET_H

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
#include <matplot/matplot.h>


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
    MyQGraphicsRectItem* CreateMyItamVerties(const int& x,const int& y,const int& r,
                                             const QPen& pen, const QBrush& brush);

signals:
    void signalFromButton(QString str);

public slots:

    void slotButtonChoose();
    void onStepTimer();

private:

    std::vector<MyQGraphicsRectItem*> Vec_Item;
    QTimer* stepTimer;
    QGraphicsScene* scen;
    MyGraphicsView* view;
    QPushButton* buttonBack;
    QPushButton* buttonStart;
    QPushButton* buttonChooseFile;
    QTimer* animatiomTimer;



};

#endif // STARTWIDGET_H

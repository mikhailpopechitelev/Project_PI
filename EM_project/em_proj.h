#ifndef EM_PROJ_H
#define EM_PROJ_H
#include "menu.h"
#include "autors.h"
#include "startwidget.h"
#include "graph_parser.h"
#include <QPushButton>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLayout>
#include <QStackedWidget>


class EM_proj : public QWidget
{
    Q_OBJECT
public:
    //поля всего проекта
    QStackedWidget* stack;
    Menu* startmenu = new Menu();
    StartWidget* startWidget = new StartWidget();
    Authors* authorsWidget = new Authors();

    //работа со стеком
    void pushStack(QWidget* wgt);
    void popStack();

    //работа с графами считанными из файла
    void loadfile(const std::string& url);
    void addScengraph(std::pair<std::vector<Edges>,std::vector<Vertices>>& mas);
    std::pair<std::vector<Edges>,std::vector<Vertices>> getMasVE(const std::string& url);
    std::vector<std::pair<int,int>> findMinPointMaxPoint(
              std::pair<std::vector<Edges>,std::vector<Vertices>>& mas);

    //методы создания вершин и ребер
    QGraphicsEllipseItem* CreateItamVerties(const int& x,const int& y,const int& r,const QPen& pen, const QBrush& brush);
    QGraphicsLineItem* CreateItamEdges(const int& x1,const int& y1,
                                   const int& x2,const int& y2,
                                   const QPen& pen);

    explicit EM_proj(QWidget *parent = nullptr);
private slots:
    void slotButtonStart();
    void SlotButtonAutors();
    void SlotButtonQuite();
    void slotButtonBack();
    void slotButtonChoose();
};

#endif // EM_PROJ_H

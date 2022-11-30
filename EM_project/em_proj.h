#ifndef EM_PROJ_H
#define EM_PROJ_H
//подключаемые библиотеки
#include "menu.h"
#include "autors.h"
#include "startwidget.h"
#include "graph_parser.h"
#include "myqgraphicsrectiten.h"
#include <QPushButton>
#include <QGraphicsSimpleTextItem>
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
    void parseTgf(const std::string& url,std::vector<std::string>& edges_name,
                  std::vector<std::pair<size_t,size_t>>& edges);
    //загрузка файла и его парсер через *.graph и *.tgf
    void loadfile(const std::string& url);

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

    //пока не используемая функция разположение текста на графе
    QGraphicsSimpleTextItem* CreateItamSimpleText();
    explicit EM_proj(QWidget *parent = nullptr);

private slots:    

    //слоты для кнопок приложения
    void slotButtonStart();
    void SlotButtonAutors();
    void SlotButtonQuite();
    void slotButtonBack();
    void slotButtonChoose();

};

#endif // EM_PROJ_H

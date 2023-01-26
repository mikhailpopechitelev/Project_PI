

#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QPushButton>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLayout>
#include <QStackedWidget>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QGraphicsItem>

/**
*  @brief класс моего отображения для графа унаследованного от QGraphicsView
*/
class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:

    /**
    *  @brief конструктор создания моего поля для отображения графа
    *  @param scen указатель на сцену на которую выставлены объекты для отображения
    */
    explicit MyGraphicsView(QGraphicsScene* scen, QWidget *parent = nullptr);

    /**
    *  @brief переопределение базового метода прокрутки колеса мыши
    */
    void wheelEvent(QWheelEvent* event) override;

signals:

};

#endif // MYGRAPHICSVIEW_H

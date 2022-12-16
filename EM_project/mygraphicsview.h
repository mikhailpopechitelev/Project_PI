

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


class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:

    explicit MyGraphicsView(QGraphicsScene* scen, QWidget *parent = nullptr);
    void wheelEvent(QWheelEvent* event) override;

signals:

};

#endif // MYGRAPHICSVIEW_H

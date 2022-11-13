#ifndef STARTWIDGET_H
#define STARTWIDGET_H
#include <mygraphicsview.h>
#include <QPushButton>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLayout>
#include <QStackedWidget>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>



class StartWidget: public QWidget
{
    Q_OBJECT
public:
    QPushButton* buttonBack = new QPushButton("Back");
    QPushButton* buttonStart = new QPushButton("Start");
    QPushButton* buttonChooseFile = new QPushButton("Choose file");
    QGraphicsScene* scen = new QGraphicsScene(QRectF(-500,-500,1000,1000));
    MyGraphicsView* view = new MyGraphicsView(scen);
    //QGraphicsView* view = new  QGraphicsView(scen);

    explicit StartWidget(QWidget *parent = nullptr);

public:
    void sendButtonQuite(){
        emit signalFromButton("Back");
    };
signals:
    void signalFromButton(QString str);
public slots:

};

#endif // STARTWIDGET_H

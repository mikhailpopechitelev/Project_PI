#ifndef STARTWIDGET_H
#define STARTWIDGET_H
#include <QPushButton>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLayout>
#include <QStackedWidget>

class StartWidget: public QWidget
{
    Q_OBJECT
public:
    QPushButton* buttonBack = new QPushButton("Back");
    QPushButton* buttonStart = new QPushButton("Start");
    QPushButton* buttonChooseFile = new QPushButton("Choose file");
    explicit StartWidget(QWidget *parent = nullptr);

public:
    void slotButtonQuite(){
        emit signalFromButton("Back");
    };
signals:
    void signalFromButton(QString str);
    //void clicked(QStackedWidget* stack);
public slots:

};

#endif // STARTWIDGET_H

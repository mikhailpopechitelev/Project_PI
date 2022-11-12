#ifndef EM_PROJ_H
#define EM_PROJ_H
#include "menu.h"
#include "autors.h"
#include "startwidget.h"
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
    QStackedWidget* stack;
    Menu* startmenu = new Menu();
    StartWidget* startWidget = new StartWidget();
    Authors* authorsWidget = new Authors();
    /*
    enum class eState{
        MENU,
        START,
        EXIT
    };
    enum class eMenu{
        START =-1,
        EXIT,
        END
    };

    */


    void pushStack(QWidget* wgt);
    void popStack();
    friend void popStackS(EM_proj proj);

    explicit EM_proj(QWidget *parent = nullptr);

public:
    void sendSignalButton(){
        emit signalFromButton("start");
    }
    void sendSignalButtonAutors(){
        emit signalFromButton("Authors");
    };
    void sendButtonQuite(){
        emit signalFromButton("Quit");
    };
    void sendButtonChoose(){
        emit signalFromButton("Choose file");
    }
signals:
    void signalFromButton(QString str);

private slots:
    void slotButtonStart();
    void SlotButtonAutors();
    void SlotButtonQuite();
    void slotButtonBack();
    void slotButtonChoose();
};

#endif // EM_PROJ_H

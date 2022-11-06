#ifndef EM_PROJ_H
#define EM_PROJ_H
#include "menu.h"
#include "autors.h"
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
    QStackedWidget* stack = new QStackedWidget();
    Menu menu;
    Authors autorsWidget;
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
    explicit EM_proj(QWidget *parent = nullptr);

    void sendSignalButton(){
        emit signalFromButton("start");
    }
signals:
    void signalFromButton(QString str);
/*
private:
    void _proccessing();
    void _draw();

private:
    eState mState{eState::MENU};
    eMenu mCurrentMenu;
    std::vector<std::pair<eMenu,std::string>> mvMenu;
    */

private slots:
    void slotButtonStart();
    //void SlotButtonAutors();
    //void SlotButtonQuite();
};

#endif // EM_PROJ_H

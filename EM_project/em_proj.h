#ifndef EM_PROJ_H
#define EM_PROJ_H
//подключаемые библиотеки
#include <menu.h>
#include <startwidget.h>
#include <QFileDialog>
#include <autors.h>
#include <QtCore>
#include <QDebug>
#include <myqgraphicsrectiten.h>
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
    //получить стек
    QStackedWidget* getSteck();

    //работа со стеком
    void pushStack(QWidget* wgt);
    void popStack();  
    explicit EM_proj(QWidget *parent = nullptr);

private:
    //поля всего проекта
    QStackedWidget* stack;
    Menu* startmenu;
    StartWidget* startWidget;
    Authors* authorsWidget;

private slots:    

    //слоты для кнопок приложения
    void slotButtonStart();
    void SlotButtonAutors();
    void SlotButtonQuite();
    void slotButtonBack();
};

#endif // EM_PROJ_H

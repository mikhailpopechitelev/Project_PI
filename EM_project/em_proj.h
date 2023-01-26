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

/**
*  @brief класс моего проекта унаследованный от исходного Widget
*/
class EM_proj : public QWidget
{
    Q_OBJECT
public:
    /**
    *  @brief функция получения стека
    *  @return возвращает стек
    */
    QStackedWidget* getSteck();

    /**
    *  @brief добавление в стек
    *  @param wgt виджет для добавления
    */
    void pushStack(QWidget* wgt);
    /**
    *  @brief удаление из стека
    */
    void popStack();  
    /**
     *  @brief конструктор проекта
     */
    explicit EM_proj(QWidget *parent = nullptr);

private:
    //!поля всего проекта
    QStackedWidget* stack;
    Menu* startmenu;
    StartWidget* startWidget;
    Authors* authorsWidget;

private slots:    

    //!слоты для кнопок приложения
    void slotButtonStart();
    void SlotButtonAutors();
    void SlotButtonQuite();
    void slotButtonBack();
};

#endif // EM_PROJ_H

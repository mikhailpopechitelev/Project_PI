#ifndef MENU_H
#define MENU_H
#include <QPushButton>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLayout>
#include <QStackedWidget>
#include <QWidget>
#include <QDebug>
/**
*  @brief класс стартового меня унаследованного от QWidget
*/
class Menu : public QWidget
{
    Q_OBJECT

public:

    /**
    *  @brief конструктор меню начального
    */
    explicit Menu(QWidget *parent = nullptr);

signals:


private:
    //!поля стартового приложения
    QPushButton* start;
    QPushButton* authors;
    QPushButton* quit;
};

#endif // MENU_H

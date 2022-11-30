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

class Menu : public QWidget
{
    Q_OBJECT
public:

    //конструтор меню
    explicit Menu(QWidget *parent = nullptr);

signals:


private:
    //поля стартового приложения
    QPushButton* start;
    QPushButton* authors;
    QPushButton* quit;
};

#endif // MENU_H

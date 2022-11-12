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
    QPushButton* start = new QPushButton("Start");
    QPushButton* authors = new QPushButton("Authors");
    QPushButton* quit = new QPushButton("Quit");
    explicit Menu(QWidget *parent = nullptr);

signals:

};

#endif // MENU_H

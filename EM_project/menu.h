#ifndef MENU_H
#define MENU_H


#include <QQuickWidget>
#include <QQuickItem>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLayout>
#include <QWidget>



class Menu : public QWidget
{
    Q_OBJECT
public:

    Menu(QWidget* pwgt = nullptr);
    ~Menu() = default;
private:
    //QWidget* pwgt = nullptr;
    //QWidget* QWidget = nullptr;

};

#endif // MENU_H

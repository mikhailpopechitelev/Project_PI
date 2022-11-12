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

    void loadfile(const std::string& url);
    void pushStack(QWidget* wgt);
    void popStack();
    QGraphicsEllipseItem* CreateItamVerties(const int& x,const int& y,const int& r,const QPen& pen, const QBrush& brush);
    QGraphicsItem* CreateItamEdges(const int& from,const int& to);

    explicit EM_proj(QWidget *parent = nullptr);

private slots:
    void slotButtonStart();
    void SlotButtonAutors();
    void SlotButtonQuite();
    void slotButtonBack();
    void slotButtonChoose();
};

#endif // EM_PROJ_H

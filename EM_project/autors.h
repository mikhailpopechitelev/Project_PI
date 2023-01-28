#ifndef AUTORS_H
#define AUTORS_H
#include <QPushButton>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLayout>
#include <QStackedWidget>
#include <QWidget>

class Authors : public QWidget
{
    Q_OBJECT
public:

    explicit Authors(QWidget *parent = nullptr);

private:

    QPushButton* buttonBack_a;

signals:

};

#endif // AUTORS_H

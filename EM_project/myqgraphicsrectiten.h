#ifndef MYQGRAPHICSRECTITEN_H
#define MYQGRAPHICSRECTITEN_H

#include <QPainter>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QAbstractGraphicsShapeItem>
#include <QGraphicsItem>

/**
*  @brief класс моего отображения для узла графа унаследованного от базового прямоугольника
*/
class MyQGraphicsRectItem : public QGraphicsRectItem
{
    //Q_OBJECT
public:
    /**
    *  @brief констуктор
    */
    explicit MyQGraphicsRectItem(const qreal& x,const qreal& y,const int& r);
    /**
    *  @brief деструктор узла графа
    */
    ~MyQGraphicsRectItem() = default;
    /**
    *  @brief выделение места на сцене под узел графа
    */
    QRectF boundingRect() const;
    /**
    *  @brief функция отрисовки узла графа
    *  @param painter стиль отрисовки узла
    *  @param option не используемый параметр
    *  @return widget родительский класс
    */

    void paint(QPainter* painter,
                const QStyleOptionGraphicsItem* option, QWidget* widget);

    /**
    *  @brief функция которая логически убивает узел
    */
    void dead();
    /**
    *  @brief функция которая логически инфицирует узел
    */
    void sick();
    /**
    *  @brief функция которая логически выздоравлевает узел
    */
    void recover();
    /**
    *  @brief функция которая заражает узел
    */
    void infected();

    void unrecovered();

    /**
    *  @brief функция проверяющая на болезнь
    *  @return результат проверки
    */
    bool isSick();
    /**
    *  @brief функция проверяющая на смерть узел
    *  @return результат проверки
    */
    bool isDead();
    /**
    *  @brief функция проверяющая на инфицированность
    *  @return результат проверки
    */
    bool isInfectd();
    void print_id();
    /**
    *  @brief функция проверяющая на вызжоровление
    *  @return результат проверки
    */
    bool isRecover();

    /**
    *  @brief функция получающая количнство дней узла
    *  @return количнство дней
    */
    int get_day();
    int day_sick =0 ;
    int day_recovered = 0;
public:
    virtual void advance(int phase);

signals:


private:
    //!поля узла
    //! \code
    bool m_infected = false;
    bool m_dead = false;
    bool m_recover = false;
    bool m_sick = false;
    qreal m_x=0;
    qreal m_y=0;
    int r =0;
    ///\endcode
};

#endif // MYQGRAPHICSRECTITEN_H

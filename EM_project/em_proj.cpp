#include <em_proj.h>

QStackedWidget* EM_proj::getSteck(){
    return this->stack;
}

//создание конструктора
EM_proj::EM_proj(QWidget *parent)
    : QWidget{parent}
{
    startmenu = new Menu(this);
    startWidget = new StartWidget(this);
    authorsWidget = new Authors(this);

    //!создание стка
    stack = new QStackedWidget();
    stack->addWidget(startmenu);

    //!создание расстановки
    QVBoxLayout* layout = new QVBoxLayout();

    //!расстановка стека виджетов при создании проекта
    layout->addWidget(stack);
    this->setLayout(layout);
}

//!методы заполнения стека и удаления из стека
void EM_proj::pushStack(QWidget* wgt){
    stack->addWidget(wgt);
}
void EM_proj::popStack(){
    stack->removeWidget(stack->currentWidget());
}

//!реализация словот кнопок
void EM_proj::slotButtonBack(){
    stack->removeWidget(stack->currentWidget());
    stack->setCurrentWidget(stack->currentWidget());
}
//!добавление в стек виджета при отправлении игнала с кнопки
void EM_proj::slotButtonStart(){
    stack->addWidget(startWidget);
    stack->setCurrentWidget(startWidget);
}
//!добавление в стек виджета при отправлении игнала с кнопки
void EM_proj::SlotButtonAutors(){
    stack->addWidget(authorsWidget);
    stack->setCurrentWidget(authorsWidget);
}
//!добавление в стек виджета при отправлении игнала с кнопки
void EM_proj::SlotButtonQuite(){
    qApp->quit();
}



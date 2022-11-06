#include "startwidget.h"

StartWidget::StartWidget()
{
    QPushButton* buttonBack = new QPushButton;
    QVBoxLayout* BoxLayout = new QVBoxLayout;
    BoxLayout->addWidget(buttonBack);
    this->setLayout(BoxLayout);
}

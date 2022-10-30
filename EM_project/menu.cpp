#include "menu.h"
#include <stdio.h>

Menu::Menu(QWidget* pwgt/*=0*/) : QWidget(pwgt)
{
    QQuickWidget* pv = new QQuickWidget(QUrl("qrc:/Button.qml") );
    QVBoxLayout* pvbx = new QVBoxLayout;
    pvbx->addWidget(pv);
    this->setLayout(pvbx);
    /*
    QQuickItem* pqiRoot = pv->rootObject();
    pqiRoot->setProperty ( "color", "yellow");
    //pv->show();
    */

    QQuickItem* pqiRoot = pv->rootObject();
    if(pqiRoot)
      pqiRoot->setProperty ( "color", "yellow");
      QObject* pObjText = pqiRoot->findChild<QObject*>("lext");
    if(pObjText){
        pObjText->setProperty ( "text", "Good bye, world!") ;
        pObjText->setProperty ( "color", "blue");

        QVariant varRet;
        QMetaObject::invokeMethod(pObjText,
                                "setFontSize",
                                Q_RETURN_ARG(QVariant, varRet),
                                Q_ARG(QVariant, 52)
        );
        qDebug () << varRet;

    }




}


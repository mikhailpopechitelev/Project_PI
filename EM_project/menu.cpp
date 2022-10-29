#include "menu.h"
#include <stdio.h>

Menu::Menu(QWidget* pwgt/*=0*/) : QWidget(pwgt)
{

    QQuickWidget* pv = new QQuickWidget(QUrl("qrc:/main.qml") );
    QVBoxLayout* pvbx = new QVBoxLayout;
    pvbx->addWidget(pv);
    setLayout(pvbx);
    //pv->show();


    QQuickItem* pqiRoot = pv->rootObject();
    if(pqiRoot)
        pqiRoot->setProperty ( "color", "yellow");
    QObject* pObjText = pqiRoot->findChild<QObject*>("text");
    if(pObjText){
        pObjText->setProperty ( "text", "Good bye, world!") ;
        pObjText->setProperty ( "color", "Bluе");

        QVariant varRet;
        QMetaObject::invokeMethod(pObjText,
                                "setFontSize",
                                Q_RETURN_ARG(QVariant, varRet),
                                Q_ARG(QVariant, 52)
        );
        qDebug () << varRet;

    }


}


#include "cppconnection.h"

CppConnection::CppConnection(QObject *parent)
    : QObject{parent}
{

}
void CppConnection::slotQuite(){
    qApp->quit();
}

void CppConnection::slotInfo(const QString& str){
    qDebug() <<str;
}

void CppConnection::slotChangeColor(){

    /*
    QQmlComponent comp(QUrl("qrc:/main.qml"));
    QObject* pobj = comp.create();
    QObject* pv =
    */
    QQuickView view;
    view.setSource(QUrl("qrc:/main.qml"));
    QObject* object = view.rootObject();
    QQuickItem* pqiRoot = qobject_cast<QQuickItem*>(object);
    QObject* pObjText = pqiRoot->findChild<QObject*>("ColorChanButton");
    qDebug () << pObjText->objectName() ;
    if(pObjText){
        pObjText->setProperty ( "text", "Changed") ;
        pObjText->setProperty ( "color", "red");
    }else if (pObjText)
        pObjText->setProperty ( "text", "NotChanged") ;
        pObjText->setProperty ( "color", "blue");

}

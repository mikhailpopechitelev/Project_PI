#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QUrl>
#include <QColor>


#include <QLocale>
#include <QTranslator>

#include <menu.h>
#include "cppconnection.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    //QApplication app(argc, argv); //Gui
    QGuiApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "EM_project_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    //Menu menu;
    //menu.show();

    QQmlApplicationEngine eng;
    QQmlComponent comp(&eng, QUrl("qrc:/main.qml"));
    QObject* pobj = comp.create();
    CppConnection cc;


    QObject* pcmdQuiteButton = pobj->findChild<QObject*>("QuiteButton");

    if  (pcmdQuiteButton){
        QObject::connect(pcmdQuiteButton,SIGNAL(quiteClicked()),&cc,SLOT(slotQuite()));
    }
    QObject* pcmdInfoButton = pobj->findChild<QObject*>("InfoButton");
    if  (pcmdInfoButton){
        QObject::connect(pcmdInfoButton,SIGNAL(infoclicked(QString)),&cc,SLOT(slotInfo(QString)));
    }
    QObject* pcmdChangeColorButton = pobj->findChild<QObject*>("ColorChanButton");
    if  (pcmdChangeColorButton){
        QObject::connect(pcmdChangeColorButton,SIGNAL(colorChanClicked()),&cc,SLOT(slotChangeColor()));
    }

    return app.exec();
}










/*
QQmlApplicationEngine engine;

const QUrl url(QStringLiteral("qrc:/main.qml"));
QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                 &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
        QCoreApplication::exit(-1);
}, Qt::QueuedConnection);


engine.load(url);

*/

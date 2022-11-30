#include <QApplication>
#include "em_proj.h"
#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <human.h>
//#include <gvc.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "EM_project_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    EM_proj main;
    //Human* hum;
    //main.startWidget->scen->addItem(hum);
    main.resize(800,600);
    main.show();


    return a.exec();
}

#include <QApplication>
#include <em_proj.h>
#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle("QFusionStyle");
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "EM_project_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    //!создание объекта моего проекта и отобрадение его в полный экран
    EM_proj main;
    main.show();
    //main.showFullScreen();


    return a.exec();
}

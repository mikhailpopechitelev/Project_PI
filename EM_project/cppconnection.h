#ifndef CPPCONNECTION_H
#define CPPCONNECTION_H

#include <QObject>
#include <QtCore>
#include <QQuickItem>
#include <QQuickView>

class CppConnection : public QObject
{
    Q_OBJECT
public:
    explicit CppConnection(QObject *parent = nullptr);

signals:

public slots:
    void slotQuite();
    void slotChangeColor();
    void slotInfo(const QString& str);
};

#endif // CPPCONNECTION_H

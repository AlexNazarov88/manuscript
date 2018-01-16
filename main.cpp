#include <QApplication>
#include <QQmlApplicationEngine>

#include <QtQuickControls2>
#include <QQuickStyle>

#include <QDebug>

#include "editmodule.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<EditModule>("sparkly.editmodule", 0, 1, "EditModule");

    QQuickStyle::setStyle("Imagine");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    QString version = QString("Manuscript v%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_BUILD);
    qDebug()<< version;

    return app.exec();
}

//#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>

#include "editmodule.h"

int main(int argc, char *argv[])
{
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    qmlRegisterType<EditModule>("sparkly.editmodule", 1, 0, "EditModule");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

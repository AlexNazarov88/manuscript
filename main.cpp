#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDebug>

#include "mainwindow.h"

int main(int argc, char *argv[])
{

    Q_INIT_RESOURCE(app_res);

    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Sparkly");
    QCoreApplication::setApplicationName("Manuscript");
    //
    QString version = QString("Manuscript v%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_BUILD);
    qDebug()<< version;
    QCoreApplication::setApplicationVersion(version/*QT_VERSION_STR*/);

    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);

    app.setWindowIcon(QIcon(":icons/scroll.ico"));

    MainWindow mainWin;
    if (!parser.positionalArguments().isEmpty())
        mainWin.loadFile(parser.positionalArguments().first());
    mainWin.show();
    return app.exec();
}

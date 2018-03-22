#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDebug>
#include <QStatusBar>

#include "core.h"
#include "mainwindow.h"
#include "editor.h"


void connectSignals(FakeVimHandler &handler, Core &Core)
{
    QObject::connect(&handler, &FakeVimHandler::commandBufferChanged,
        &Core, &Core::changeStatusMessage);
    QObject::connect(&handler, &FakeVimHandler::extraInformationChanged,
        &Core, &Core::changeExtraInformation);
    QObject::connect(&handler, &FakeVimHandler::statusDataChanged,
        &Core, &Core::changeStatusData);
    QObject::connect(&handler, &FakeVimHandler::highlightMatches,
        &Core, &Core::highlightMatches);
    QObject::connect(&handler, &FakeVimHandler::handleExCommandRequested,
        &Core, &Core::handleExCommand);
    QObject::connect(&handler, &FakeVimHandler::requestSetBlockSelection,
        &Core, &Core::requestSetBlockSelection);
    QObject::connect(&handler, &FakeVimHandler::requestDisableBlockSelection,
        &Core, &Core::requestDisableBlockSelection);
    QObject::connect(&handler, &FakeVimHandler::requestHasBlockSelection,
        &Core, &Core::requestHasBlockSelection);

    QObject::connect(&Core, &Core::handleInput,
        &handler, [&] (const QString &text) { handler.handleInput(text); });
}


QWidget *createEditorWidget(bool usePlainTextEdit)
{
    QWidget *editor = 0;
    if (usePlainTextEdit) {
        Editor<QPlainTextEdit> *w = new Editor<QPlainTextEdit>;
        w->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        editor = w;
    } else {
        Editor<QTextEdit> *w = new Editor<QTextEdit>;
        w->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        editor = w;
    }
    editor->setObjectName(_("Editor"));
    editor->setFocus();

    //
    QFont font;
    font.setFamily(_("Fixedsys"));
    //font.setFamily(_("Fixedsys"));
    font.setPointSize(9);
    editor->setFont(font);
    //

    return editor;
}

void initHandler(FakeVimHandler &handler)
{
    handler.handleCommand(_("set nopasskeys"));
    handler.handleCommand(_("set nopasscontrolkey"));

    // Set some Vim options.
    handler.handleCommand(_("set expandtab"));
    handler.handleCommand(_("set shiftwidth=8"));
    handler.handleCommand(_("set tabstop=16"));
    handler.handleCommand(_("set autoindent"));

    // Try to source file "fakevimrc" from current directory.
    handler.handleCommand(_("source fakevimrc"));

    handler.installEventFilter();
    handler.setupWidget();
}

void initMainWindow(QMainWindow &mainWindow, QWidget *centralWidget)
{
    //mainWindow.setWindowTitle(QString(_("Manuscript"))); //
    mainWindow.setCentralWidget(centralWidget);
    mainWindow.resize(600, 650);
    mainWindow.move(0, 0);
    mainWindow.show();

    // Set monospace font for editor and status bar.
    QFont font = QApplication::font(); //
    font.setFamily(_("Monospace"));
    //font.setFamily(_("Fixedsys"));
    //font.setPointSize(9);
    centralWidget->setFont(font);
    mainWindow.statusBar()->setFont(font);


}

void clearUndoRedo(QWidget *editor)
{
    EDITOR(editor, setUndoRedoEnabled(false));
    EDITOR(editor, setUndoRedoEnabled(true));
}

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(app_res);
    QApplication app(argc, argv);

    QString version = QString("Manuscript v%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_BUILD);
    qDebug()<< version;
    app.setWindowIcon(QIcon(":icons/scroll.ico"));

    QStringList args = app.arguments();

    // If FAKEVIM_PLAIN_TEXT_EDIT environment variable is 1 use QPlainTextEdit instead on QTextEdit;
    bool usePlainTextEdit = qgetenv("FAKEVIM_PLAIN_TEXT_EDIT") == "1";

    // Create editor widget.
    QWidget *editor = createEditorWidget(usePlainTextEdit); //

    // Create FakeVimHandler instance which will emulate Vim behavior in editor widget.
    FakeVimHandler handler(editor, 0);

    // Create main window.
    MainWindow mainWindow;
    initMainWindow(mainWindow, editor);

    // Connect slots to FakeVimHandler signals.
    Core core(editor, &mainWindow);
    connectSignals(handler, core);

    // Initialize FakeVimHandler.
    initHandler(handler); //

    // Clear undo and redo queues.
    clearUndoRedo(editor); //

    return app.exec();
}

//#include "main.moc"


/*
int main(int argc, char *argv[])
{

    Q_INIT_RESOURCE(app_res);


    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Sparkly");
    QCoreApplication::setApplicationName("Manuscript");
    //
    QString version = QString("Manuscript v%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_BUILD);
    qDebug()<< version;


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
*/
   // QCoreApplication::setApplicationVersion(version/*QT_VERSION_STR*/);

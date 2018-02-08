#include "mainwindow.h"


MainWindow::MainWindow(QWidget* pwgt)
    : QMainWindow(pwgt)
{
    setMinimumSize(300, 150);

    editor = new EditorModule();

    setCentralWidget(editor);
}


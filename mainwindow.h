#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "editormodule.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:

    EditorModule* editor;

};
#endif // MAINWINDOW_H

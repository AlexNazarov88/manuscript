#ifndef CORE_H
#define CORE_H

#include "fakevimhandler.h"

#include <QTimer>
class QApplication;
class QFontMetrics;
class MainWindow;
class QMessageBox;
class QPainter;
class QPlainTextEdit;
class QStatusBar;
class QTextBlock;
class QTextStream;
class QTemporaryFile;
class QTimer;
class QFile;


typedef QLatin1String _;  // create global.h and move there
const QString appName = " - Manuscript"; //

using namespace FakeVim::Internal;

// - questionable / has errors / yet to be tested

#define EDITOR(editor, call) \
    if (QPlainTextEdit *ed = qobject_cast<QPlainTextEdit *>(editor)) { \
        (ed->call); \
    } else if (QTextEdit *ed = qobject_cast<QTextEdit *>(editor)) { \
        (ed->call); \
    }


class Title //
{
public:

    void updateTitle();
    QString title() { return title; }
    //bool isModified() { return isDocModified; }
    void setModifiedMark() { name += "*";}

private:
    QString name;
    //bool isDocModified;
    QString path;
    QString title;

};

class Core : public QObject
{
    Q_OBJECT

public:


    Core(QWidget *widget, MainWindow *mw, QObject *parent = 0)  // needs to go away from here to cpp file
      : QObject(parent), m_widget(widget), m_mainWindow(mw)
    {
        QTimer::singleShot(0, this, SLOT(parseArguments())); // ?
        //setCurrentFile(QString()); //

        connect(document(), &QTextDocument::contentsChanged, this, &Core::documentWasModified);
    }

    void openFile(const QString &fileName); // deprecated


signals:
    void handleInput(const QString &keys);

public slots:
    void changeStatusData(const QString &info);
    void highlightMatches(const QString &pattern);
    void changeStatusMessage(const QString &contents, int cursorPos);
    void changeExtraInformation(const QString &info);
    void updateStatusBar();
    void handleExCommand(bool *handled, const ExCommand &cmd);
    void requestSetBlockSelection(const QTextCursor &tc);
    void requestDisableBlockSelection();
    void updateBlockSelection();
    void requestHasBlockSelection(bool *on);

private slots:
    void parseArguments(); //
    void documentWasModified();

private:
    void updateExtraSelections();
    bool wantSaveAndQuit(const ExCommand &cmd);
    bool wantSave(const ExCommand &cmd);
    bool wantQuit(const ExCommand &cmd);
    bool wantOpen(const ExCommand &cmd);
    bool wantNew(const ExCommand &cmd);
    bool wantSaveAs(const ExCommand &cmd);

    //
    bool save(); // deprecated
    void cancel();
    void invalidate();
    bool hasChanges();
    bool open(); //
    bool saveAs(); //
    bool newFile(); //
    void loadFile(const QString &fileName); //
    bool saveFile(const QString &fileName); //

    bool maybeSave(); //
    void setCurrentFile(const QString &fileName); //
    QString strippedName(const QString &fullFileName); //
    QString strippedPath(const QString &fullFileName); //
    void updateTitle(QString filePath, bool modMark=false, const QString app=appName);
    void showTitle(QString shownName);
    //

    QTextDocument *document() const;
    QString content() const;

    QWidget *m_widget;
    MainWindow *m_mainWindow;
    QString m_statusMessage;
    QString m_statusData;
    QString m_fileName;

    bool m_docModified;
    QString m_title;

    QList<QTextEdit::ExtraSelection> m_searchSelection;
    QList<QTextEdit::ExtraSelection> m_clearSelection;
    QList<QTextEdit::ExtraSelection> m_blockSelection;
};

#endif // CORE_H

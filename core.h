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


typedef QLatin1String _;

using namespace FakeVim::Internal;


#define EDITOR(editor, call) \
    if (QPlainTextEdit *ed = qobject_cast<QPlainTextEdit *>(editor)) { \
        (ed->call); \
    } else if (QTextEdit *ed = qobject_cast<QTextEdit *>(editor)) { \
        (ed->call); \
    }


class Core : public QObject
{
    Q_OBJECT

public:
    //Core(QWidget *widget, MainWindow *mw, QObject *parent);

    Core(QWidget *widget, MainWindow *mw, QObject *parent = 0)
      : QObject(parent), m_widget(widget), m_mainWindow(mw)
    {
        QTimer::singleShot(0, this, SLOT(parseArguments()));
    }

    void openFile(const QString &fileName);


    //QWidget *createEditorWidget(bool usePlainTextEdit);

    //void initHandler(FakeVimHandler &handler);
    //void initMainWindow(MainWindow &mainWindow, QWidget *centralWidget, const QString &title);
    //void clearUndoRedo(QWidget *editor);

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
    void parseArguments();

private:
    void updateExtraSelections();
    bool wantSaveAndQuit(const ExCommand &cmd);
    bool wantSave(const ExCommand &cmd);
    bool wantQuit(const ExCommand &cmd);
    bool wantOpen(const ExCommand &cmd);
    bool wantNew(const ExCommand &cmd);
    bool wantSaveAs(const ExCommand &cmd);

    bool save();
    void cancel();
    void invalidate();
    bool hasChanges();
    bool open(); //
    bool saveAs(); //
    bool newFile(); //

    bool saveFile(const QString &fileName); //

    QTextDocument *document() const;
    QString content() const;
    void setContent(QFile &file);

    QWidget *m_widget;
    MainWindow *m_mainWindow;
    QString m_statusMessage;
    QString m_statusData;
    QString m_fileName;

    QList<QTextEdit::ExtraSelection> m_searchSelection;
    QList<QTextEdit::ExtraSelection> m_clearSelection;
    QList<QTextEdit::ExtraSelection> m_blockSelection;
};

#endif // CORE_H

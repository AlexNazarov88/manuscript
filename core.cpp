#include <QtWidgets>
#include <QApplication>
#include <QFontMetrics>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QPlainTextEdit>
#include <QStatusBar>
#include <QTextBlock>
#include <QTextEdit>
#include <QTextStream>
#include <QTemporaryFile>
#include <QTimer>
#include <QFileDialog>

#include "core.h"
#include "mainwindow.h"

/*
Core::Core(QWidget *widget, QMainWindow *mw, QObject *parent = 0)
  : QObject(parent), m_widget(widget), m_mainWindow(mw)
{
    QTimer::singleShot(0, this, SLOT(parseArguments()));
}
*/



void Core::openFile(const QString &fileName) //
{
    //emit handleInput(QString(_(":r %1<CR>")).arg(fileName)); // not working well with other functions

    m_fileName = fileName;
}

//public slots
void Core::changeStatusData(const QString &info)
{
    m_statusData = info;
    updateStatusBar();
}

void Core::highlightMatches(const QString &pattern)
{
    QTextEdit *ed = qobject_cast<QTextEdit *>(m_widget);
    if (!ed)
        return;

    QTextCursor cur = ed->textCursor();

    QTextEdit::ExtraSelection selection;
    selection.format.setBackground(Qt::yellow);
    selection.format.setForeground(Qt::black);

    // Highlight matches.
    QTextDocument *doc = ed->document();
    QRegExp re(pattern);
    cur = doc->find(re);

    m_searchSelection.clear();

    int a = cur.position();
    while ( !cur.isNull() ) {
        if ( cur.hasSelection() ) {
            selection.cursor = cur;
            m_searchSelection.append(selection);
        } else {
            cur.movePosition(QTextCursor::NextCharacter);
        }
        cur = doc->find(re, cur);
        int b = cur.position();
        if (a == b) {
            cur.movePosition(QTextCursor::NextCharacter);
            cur = doc->find(re, cur);
            b = cur.position();
            if (a == b) break;
        }
        a = b;
    }

    updateExtraSelections();
}

void Core::changeStatusMessage(const QString &contents, int cursorPos)
{
    m_statusMessage = cursorPos == -1 ? contents
        : contents.left(cursorPos) + QChar(10073) + contents.mid(cursorPos);
    updateStatusBar();
}

void Core::changeExtraInformation(const QString &info)
{
    QMessageBox::information(m_widget, tr("Information"), info);
}

void Core::updateStatusBar()
{
    int slack = 80 - m_statusMessage.size() - m_statusData.size();
    QString msg = m_statusMessage + QString(slack, QLatin1Char(' ')) + m_statusData;
    m_mainWindow->statusBar()->showMessage(msg);
}

void Core::handleExCommand(bool *handled, const ExCommand &cmd)
{
    if ( wantSaveAndQuit(cmd) ) {
        // :wq
        if (save())
            cancel();
    } else if ( wantSave(cmd) ) {
        save(); // :w
    } else if ( wantOpen(cmd) ) {
        open(); // :e
    } else if ( wantNew(cmd) ) {
        newFile(); // :enew
    } else if ( wantSaveAs(cmd) ) {
        saveAs(); // :sav
    } else if ( wantQuit(cmd) ) {
        if (cmd.hasBang)
            invalidate(); // :q!
        else
            cancel(); // :q
    } else {
        *handled = false;
        return;
    }

    *handled = true;
}

void Core::requestSetBlockSelection(const QTextCursor &tc)
{
    QTextEdit *ed = qobject_cast<QTextEdit *>(m_widget);
    if (!ed)
        return;

    QPalette pal = ed->parentWidget() != NULL ? ed->parentWidget()->palette()
                                              : QApplication::palette();

    m_blockSelection.clear();
    m_clearSelection.clear();

    QTextCursor cur = tc;

    QTextEdit::ExtraSelection selection;
    selection.format.setBackground( pal.color(QPalette::Base) );
    selection.format.setForeground( pal.color(QPalette::Text) );
    selection.cursor = cur;
    m_clearSelection.append(selection);

    selection.format.setBackground( pal.color(QPalette::Highlight) );
    selection.format.setForeground( pal.color(QPalette::HighlightedText) );

    int from = cur.positionInBlock();
    int to = cur.anchor() - cur.document()->findBlock(cur.anchor()).position();
    const int min = qMin(cur.position(), cur.anchor());
    const int max = qMax(cur.position(), cur.anchor());
    for ( QTextBlock block = cur.document()->findBlock(min);
          block.isValid() && block.position() < max; block = block.next() ) {
        cur.setPosition( block.position() + qMin(from, block.length()) );
        cur.setPosition( block.position() + qMin(to, block.length()), QTextCursor::KeepAnchor );
        selection.cursor = cur;
        m_blockSelection.append(selection);
    }

    connect( ed, &QTextEdit::selectionChanged,
             this, &Core::updateBlockSelection, Qt::UniqueConnection );

    QPalette pal2 = ed->palette();
    pal2.setColor(QPalette::Highlight, Qt::transparent);
    pal2.setColor(QPalette::HighlightedText, Qt::transparent);
    ed->setPalette(pal2);

    updateExtraSelections();
}

void Core::requestDisableBlockSelection()
{
    QTextEdit *ed = qobject_cast<QTextEdit *>(m_widget);
    if (!ed)
        return;

    QPalette pal = ed->parentWidget() != NULL ? ed->parentWidget()->palette()
                                              : QApplication::palette();

    m_blockSelection.clear();
    m_clearSelection.clear();

    ed->setPalette(pal);

    disconnect( ed, &QTextEdit::selectionChanged,
                this, &Core::updateBlockSelection );

    updateExtraSelections();
}

void Core::updateBlockSelection()
{
    QTextEdit *ed = qobject_cast<QTextEdit *>(m_widget);
    if (!ed)
        return;

    requestSetBlockSelection(ed->textCursor());
}

void Core::requestHasBlockSelection(bool *on)
{
    *on = !m_blockSelection.isEmpty();
}


//private slots
void Core::parseArguments() // needs improving
{
    QStringList args = qApp->arguments();

    //const QString editFileName = args.value(1, QString(_("/usr/share/vim/vim74/tutor/tutor"))); //
    const QString editFileName = args.value(1); //
    //openFile(editFileName);

    if (!editFileName.isEmpty()) { //
        loadFile(editFileName);
    } else {
        setCurrentFile(QString());
    }

    foreach (const QString &cmd, args.mid(2)) // ?
        emit handleInput(cmd);
}

//private
void Core::updateExtraSelections()
{
    QTextEdit *ed = qobject_cast<QTextEdit *>(m_widget);
    if (ed)
        ed->setExtraSelections(m_clearSelection + m_searchSelection + m_blockSelection);
}

bool Core::wantSaveAndQuit(const ExCommand &cmd)
{
    return cmd.cmd == "wq";
}

bool Core::wantSave(const ExCommand &cmd)
{
    return cmd.matches("w", "write") || cmd.matches("wa", "wall");
}

bool Core::wantQuit(const ExCommand &cmd)
{
    return cmd.matches("q", "quit") || cmd.matches("qa", "qall");
}

bool Core::wantOpen(const ExCommand &cmd)
{
    return cmd.cmd == "e";
}

bool Core::wantNew(const ExCommand &cmd)
{
    return cmd.cmd == "enew";
}

bool Core::wantSaveAs(const ExCommand &cmd)
{
    return cmd.cmd == "sav";
}

bool Core::save() // needs redirection in case file is not created (to saveAs()) / needs redo
{
    if (!hasChanges())
        return true;

    QTemporaryFile tmpFile;
    if (!tmpFile.open()) {
        QMessageBox::critical(m_widget, tr("Manuscript Error"),
                              tr("Cannot create temporary file: %1").arg(tmpFile.errorString()));
        return false;
    }

    QTextStream ts(&tmpFile);
    ts << content();
    ts.flush();

    QFile::remove(m_fileName);
    if (!QFile::copy(tmpFile.fileName(), m_fileName)) {
        QMessageBox::critical(m_widget, tr("Manuscript Error"),
                              tr("Cannot write to file \"%1\"").arg(m_fileName));
        return false;
    }

    return true;
}

void Core::cancel()
{
    if (hasChanges()) {
        QMessageBox::critical(m_widget, tr("Manuscript Warning"),
                              tr("File \"%1\" was changed").arg(m_fileName));
    } else {
        invalidate();
    }
}

void Core::invalidate()
{
    QApplication::quit();
}

bool Core::hasChanges()
{
    if (m_fileName.isEmpty() && content().isEmpty())
        return false;

    QFile f(m_fileName);
    if (!f.open(QIODevice::ReadOnly))
        return true;

    QTextStream ts(&f);
    return content() != ts.readAll();
}

bool Core::open()//
{

    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName();
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool Core::saveAs() //
{
    QFileDialog dialog;
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;

    return saveFile(dialog.selectedFiles().first());
}

bool Core::newFile() //
{
    if (maybeSave()) {
        document()->clear();
        setCurrentFile(QString());
    }
}


bool Core::maybeSave() //
{
    if (!document()->isModified())
        return true;
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(m_mainWindow, tr("Save files - Manuscript"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}


void Core::setCurrentFile(const QString &fileName) // -----
{
    m_fileName = fileName;
    document()->setModified(false);
    m_mainWindow->setWindowModified(false); //

    QString shownName = m_fileName;
    if (m_fileName.isEmpty())
        shownName = "untitled";
    m_mainWindow->setWindowFilePath(shownName + " - Manuscript"); //
    qDebug()<<"ended setCurrentFile";
}



bool Core::saveFile(const QString &fileName) // ----- supplement of save()
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(m_mainWindow, tr("Manuscript"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName),
                                  file.errorString()));
        return false;
    }

    QTextStream out(&file);

    out << document()->toPlainText();

    setCurrentFile(fileName);
    //openFile(fileName); //

    return true;
}

void Core::loadFile(const QString &fileName) //
{
    qDebug()<<"entered loadFile()";
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(m_mainWindow, tr("Manuscript"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);

    document()->setPlainText(in.readAll());
    setCurrentFile(fileName);
    //m_fileName = fileName;

}

QTextDocument *Core::document() const //
{
    QTextDocument *doc = NULL;
    if (QPlainTextEdit *ed = qobject_cast<QPlainTextEdit *>(m_widget))
        doc = ed->document();
    else if (QTextEdit *ed = qobject_cast<QTextEdit *>(m_widget))
        doc = ed->document();
    return doc;
}

QString Core::content() const
{
    return document()->toPlainText();
}

void Core::setContent(QFile &file)  // needs test / not needed
{
    QTextStream ts(&file);

    document()->setPlainText(ts.readAll());
    ts.flush();
}

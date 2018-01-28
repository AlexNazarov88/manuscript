#include "editorlogic.h"
#include "QDebug"

EditorLogic::EditorLogic(QWidget *parent) :
    QObject(parent)
{
    m_edit = new QPlainTextEdit();

    m_bar = new StatusBar();

    // transfer data from QML to C++
    connect(this, SIGNAL(textChanged(QString)), m_edit, SLOT(setPlainText(QString)));
    connect(m_edit->document(), SIGNAL(cursorPositionChanged(QTextCursor)), m_bar, SLOT(updateStatusBar(QTextCursor)));
}


QString         EditorLogic::text() const       { return m_edit->toPlainText(); }
QTextDocument*  EditorLogic::document() const   { return m_edit->document(); }
QTextCursor     EditorLogic::cursor() const     { return m_edit->textCursor(); }

void EditorLogic::setText(const QString &text)
{
    if ( m_edit->toPlainText() == text) {
        return;
    }

    emit textChanged(text);
    //qDebug() << m_edit->toPlainText();
}



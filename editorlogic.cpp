#include "editorlogic.h"
#include "QDebug"

EditorLogic::EditorLogic(QWidget *parent) :
    QObject(parent)
{
    m_edit = new QPlainTextEdit();

    // transfer data from QML to C++
    connect(this, SIGNAL(textChanged(QString)), m_edit, SLOT(setPlainText(QString)));
}


QString         EditorLogic::text() const       { return m_edit->toPlainText(); }
QTextDocument*  EditorLogic::document() const   { return m_edit->document(); }

void EditorLogic::setText(const QString &text)
{
    if ( m_edit->toPlainText() == text) {
        return;
    }

    emit textChanged(text);
    //qDebug() << m_edit->toPlainText();
}



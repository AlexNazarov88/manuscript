#include "editormodule.h"
#include "QDebug"

EditorModule::EditorModule(QWidget *parent) :
    QPlainTextEdit(parent)
{


}

/*
QString         EditorModule::text() const       { return m_edit->toPlainText(); }
//QTextDocument*  EditorModule::document() const   { return m_doc; m_edit->document();
//QTextCursor     EditorModule::cursor() const     { return m_edit->textCursor(); }

//
int EditorModule::cursorLine() const       { return m_edit->textCursor().blockNumber(); }

int EditorModule::cursorColumn() const     { return m_edit->textCursor().columnNumber(); }
//

void EditorModule::setText(const QString &text)
{
    if ( m_edit->toPlainText() == text) {
        return;
    }

    m_edit->setPlainText(text);
    emit textChanged();
    //qDebug() << m_edit->toPlainText();
}


void EditorModule::setDocument (QTextDocument *doc)
{
    m_doc = doc;
}


void EditorModule::setCursor( QTextCursor cursor)
{
    m_edit->setTextCursor(cursor);
}

*/

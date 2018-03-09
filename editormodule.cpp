//#include "editormodule.h"
//#include "QDebug"
/*
Editor::Editor(QWidget *parent) :
    QPlainTextEdit(parent)
{
    TextEdit::setCursorWidth(0);
}


void EditorModule::paintEvent(QPaintEvent *e)
{
    TextEdit::paintEvent(e);

    if ( !m_cursorRect.isNull() && e->rect().intersects(m_cursorRect) ) {
        QRect rect = m_cursorRect;
        m_cursorRect = QRect();
        TextEdit::viewport()->update(rect);
    }

    // Draw text cursor.
    QRect rect = TextEdit::cursorRect();
    if ( e->rect().intersects(rect) ) {
        QPainter painter(TextEdit::viewport());

        if ( TextEdit::overwriteMode() ) {
            QFontMetrics fm(TextEdit::font());
            const int position = TextEdit::textCursor().position();
            const QChar c = TextEdit::document()->characterAt(position);
            rect.setWidth(fm.width(c));
            painter.setPen(Qt::NoPen);
            painter.setBrush(TextEdit::palette().color(QPalette::Base));
            painter.setCompositionMode(QPainter::CompositionMode_Difference);
        } else {
            rect.setWidth(TextEdit::cursorWidth());
            painter.setPen(TextEdit::palette().color(QPalette::Text));
        }

        painter.drawRect(rect);
        m_cursorRect = rect;
    }
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

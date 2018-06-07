#ifndef EDITOR_H
#define EDITOR_H


#include <QObject>
#include <QPlainTextEdit>
#include <QPainter>

template <typename TextEdit>
class Editor : public TextEdit
{
public:
    Editor(QWidget *parent = 0) : TextEdit(parent)
    {
        TextEdit::setCursorWidth(0);
    }

    void paintEvent(QPaintEvent *e)
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

private:
    QRect m_cursorRect;
};


#endif // EDITOR_H



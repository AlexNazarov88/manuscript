#include "editorlogic.h"
#include "QDebug"

EditorLogic::EditorLogic(QWidget *parent) :
    QObject(parent)
{
    edit = new QPlainTextEdit();
}


QString EditorLogic::text() const
{
    return edit->toPlainText();
}

void EditorLogic::setText(const QString &text)
{
    if (edit->toPlainText() == text) {
        return;
    }

    edit->setPlainText(text);
    qDebug() << edit->toPlainText();
    emit textChanged();
}

//QTextDocument* EditorLogic::doc() const
//{ return this->document(); }


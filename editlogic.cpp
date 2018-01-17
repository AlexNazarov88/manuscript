#include "editlogic.h"
#include "QDebug"

EditLogic::EditLogic(QWidget *parent) :
    QPlainTextEdit(parent)
{

}

QString EditLogic::text() const
{
    return m_text;
}

void EditLogic::setText(QString &text)
{
    if (m_text == text) {
        return;
    }

    m_text = text;
    qDebug() << m_text;
    emit textChanged();
}

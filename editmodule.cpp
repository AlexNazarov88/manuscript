#include "editmodule.h"
#include "QDebug"

EditModule::EditModule(QWidget *parent) :
    QPlainTextEdit(parent)
{

}

QString EditModule::text() const
{
    return m_text;
}

void EditModule::setText(QString &text)
{
    if (m_text == text) {
        return;
    }

    m_text = text;
    qDebug() << m_text;
    emit textChanged();
}

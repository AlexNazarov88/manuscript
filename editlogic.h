#ifndef EDITLOGIC_H
#define EDITLOGIC_H

#include <QPlainTextEdit>
#include <QObject>

class EditLogic : public QPlainTextEdit
{
    Q_OBJECT

    Q_PROPERTY(QString m_text READ text WRITE setText NOTIFY textChanged)

public:
    EditLogic(QWidget *parent = 0);

    QString text() const;
    void setText(QString &text);

signals:
    void textChanged();

private:
    QString m_text;
};
#endif // EDITLOGIC_H

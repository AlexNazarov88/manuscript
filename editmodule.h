#ifndef EDITMODULE_H
#define EDITMODULE_H

#include <QPlainTextEdit>
#include <QObject>

class EditModule : public QPlainTextEdit
{
    Q_OBJECT

    Q_PROPERTY(QString m_text READ text WRITE setText NOTIFY textChanged)

public:
    EditModule(QWidget *parent = 0);

    QString text() const;
    void setText(QString &text);

signals:
    void textChanged();

private:
    QString m_text;
};
#endif // EDITMODULE_H

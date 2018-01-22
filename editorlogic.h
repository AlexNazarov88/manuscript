#ifndef EDITORLOGIC_H
#define EDITORLOGIC_H


#include <QObject>
#include <QPlainTextEdit>

class EditorLogic : public QObject
{
    Q_OBJECT

    //Q_PROPERTY(QString m_text READ text WRITE setText NOTIFY textChanged) //

public:
    EditorLogic(QWidget *parent = 0);

    // getters
    Q_INVOKABLE QString text() const;
    Q_INVOKABLE QTextDocument* document() const;

    // setters
    Q_INVOKABLE void setText(const QString&); //



signals:
    void textChanged(QString);

private:

    QPlainTextEdit*     m_edit;
};
#endif // EDITORLOGIC_H

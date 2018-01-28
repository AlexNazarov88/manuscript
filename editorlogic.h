#ifndef EDITORLOGIC_H
#define EDITORLOGIC_H


#include <QObject>
#include <QPlainTextEdit>
#include "statusbarlogic.h"

class EditorLogic : public QObject
{
    Q_OBJECT

    //Q_PROPERTY(QString m_text READ text WRITE setText NOTIFY textChanged) //

public:
    EditorLogic(QWidget *parent = 0);

    // getters
    Q_INVOKABLE QString text() const;
    Q_INVOKABLE QTextDocument* document() const;
    Q_INVOKABLE QTextCursor cursor() const;
    // setters
    Q_INVOKABLE void setText(const QString&); //



signals:
    void textChanged(QString);


private:

    QPlainTextEdit*     m_edit;

    StatusBar*           m_bar;

};



#endif // EDITORLOGIC_H



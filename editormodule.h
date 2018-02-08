#ifndef EDITORMODULE_H
#define EDITORMODULE_H


#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>


class EditorModule : public QPlainTextEdit
{
    Q_OBJECT

public:
    EditorModule(QWidget *parent = 0);

    // getters
    //QString text() const;
    //QTextDocument* document() const;
    //QTextCursor cursor() const;

    //int cursorLine() const; //
   // int cursorColumn() const; //


    // setters
    //void setText(const QString&);

    //void setDocument(QTextDocument*); //

    //void setCursor(const QTextCursor);


signals:
    void textChanged();


private:

    //QPlainTextEdit*     m_edit;
    //QTextDocument*      m_doc;

};

#endif // EDITORMODULE_H



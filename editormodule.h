#ifndef EDITORMODULE_H
#define EDITORMODULE_H


#include <QObject>
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


};

#endif // EDITORMODULE_H



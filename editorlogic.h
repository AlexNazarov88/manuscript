#ifndef EDITORLOGIC_H
#define EDITORLOGIC_H


#include <QObject>
#include <QPlainTextEdit>

class EditorLogic : public QObject
{
    Q_OBJECT

    Q_PROPERTY(edit->toPlainText() READ text WRITE setText NOTIFY textChanged)

public:
    EditorLogic(QWidget *parent = 0);

    QString text() const;
    void setText(const QString&);


    //QTextDocument* doc() const; //

signals:
    void textChanged();

private:

    QPlainTextEdit* edit;
    //QString m_text; //
};
#endif // EDITORLOGIC_H

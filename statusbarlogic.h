#ifndef STATUSBARLOGIC_H
#define STATUSBARLOGIC_H

#include <QObject>
#include <QTextCursor>

class StatusBar : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString m_line       READ line)
    Q_PROPERTY(QString m_column     READ column)
    Q_PROPERTY(QString m_filetype   READ filetype)
    Q_PROPERTY(QString m_syntax     READ syntax)

public:
    StatusBar(QObject *parent = 0);

    QString line();
    QString column();
    QString filetype();
    QString syntax();


private:
    QString m_line;
    QString m_column;
    QString m_filetype;
    QString m_syntax;


public slots:

    void updateStatusBar(const QTextCursor &cursor);

};

#endif // STATUSBARLOGIC_H

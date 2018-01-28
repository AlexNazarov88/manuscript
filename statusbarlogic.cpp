#include "statusbarlogic.h"
#include "QDebug"

StatusBar::StatusBar(QObject *parent) :
    QObject(parent)
{

}


QString StatusBar::line()       { return m_line; }
QString StatusBar::column()     { return m_column; }
QString StatusBar::filetype()   { return m_filetype;}
QString StatusBar::syntax()     { return m_syntax; }


void StatusBar::updateStatusBar(const QTextCursor &cursor)
{
    // if(!(m_line == cursor.blockNumber().toString()))
    m_line = "";
    m_line = cursor.blockNumber();
    qDebug() << "line: " + m_line;

    // if(!(m_column == cursor.columnNumber()))
    m_column = "";
    m_column = cursor.columnNumber();
    qDebug() << "column: " + m_column;

}

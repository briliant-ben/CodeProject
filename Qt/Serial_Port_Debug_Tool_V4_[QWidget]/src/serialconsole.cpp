#include <QApplication>
#include <QScrollBar>
#include <QClipboard>
//#include <QDebug>
#include "serialconsole.h"
#include "serialcom.h"

SerialConsole::SerialConsole(QWidget *parent) :
    QPlainTextEdit(parent)
{
    document()->setMaximumBlockCount(2000);
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);
    //this->setLocalEchoEnabled(true);
}

void SerialConsole::putData(const QString &data)
{
    if(data.back() == '\r')
        insertPlainText(data.left(data.length()-1));
    else
        insertPlainText(data);
    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}

void SerialConsole::setLocalEchoEnabled(bool set)
{
    m_localEchoEnabled = set;
}

void SerialConsole::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Control)
        return;

    if(e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_C){
        QApplication::clipboard()->setText(this->textCursor().selectedText());
        return;
    }

    static QString cmd;
    QTextCursor cursor = this->textCursor();
    cursor.movePosition(QTextCursor::End);
    this->setTextCursor(cursor);

    if(e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_V){
        //qDebug() << "ctrl+V";
        cmd.append(QApplication::clipboard()->text());
        if (m_localEchoEnabled)
            QPlainTextEdit::keyPressEvent(e);
        return;
    }

    switch (e->key()) {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Delete:
    case Qt::Key_Tab:
        break;
    case Qt::Key_Backspace:{
        //qDebug() << cmd.size();
        if(cmd.isEmpty())
            break;
        QTextCursor cursor = this->textCursor();
        if(cursor.hasSelection())
            cursor.clearSelection();
        cursor.deletePreviousChar();
        cmd.chop(1);
        break;
    }
    case Qt::Key_Return:
    case Qt::Key_Enter:{
        emit getData(cmd + "\r");
        cmd.clear();
        break;
    }
    default:
        cmd.append(e->text());
        if (m_localEchoEnabled)
            QPlainTextEdit::keyPressEvent(e);
    }
}

void SerialConsole::mousePressEvent(QMouseEvent *e)
{
    if(SerialCom::connectStatus()){
        Q_UNUSED(e);
    }else{
        QPlainTextEdit::mousePressEvent(e);
    }
}

void SerialConsole::dragEnterEvent(QDragEnterEvent *e)
{
    Q_UNUSED(e);
}

void SerialConsole::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void SerialConsole::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}


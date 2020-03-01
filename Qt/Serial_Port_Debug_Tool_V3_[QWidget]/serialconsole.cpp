#include <QScrollBar>
#include "serialconsole.h"
#include <QDebug>

SerialConsole::SerialConsole(QWidget *parent) :
    QPlainTextEdit(parent)
{
    document()->setMaximumBlockCount(2000);
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);
}

void SerialConsole::putData(const QString &data)
{
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
    switch (e->key()) {
    case Qt::Key_Backspace:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
    default:
        if (m_localEchoEnabled)
            QPlainTextEdit::keyPressEvent(e);
        emit getData(e->text());
    }
}

void SerialConsole::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    setFocus();
}

void SerialConsole::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void SerialConsole::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}

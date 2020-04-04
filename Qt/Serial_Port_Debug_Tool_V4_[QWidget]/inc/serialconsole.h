#ifndef SERIALCONSOLE_H
#define SERIALCONSOLE_H

#include <QPlainTextEdit>

class SerialConsole : public QPlainTextEdit
{
    Q_OBJECT
signals:
    void getData(const QString&);

public slots:
    void putData(const QString&);

public:
    explicit SerialConsole(QWidget *parent = nullptr);
    void setLocalEchoEnabled(bool);

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void dragEnterEvent(QDragEnterEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void contextMenuEvent(QContextMenuEvent *e) override;

private:
    bool m_localEchoEnabled = true;
};

#endif // SERIALCONSOLE_H

#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QQuickTextDocument>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

signals:

public slots:
    void setDefaultStyleSheet(QQuickTextDocument *qd);
};

#endif // BACKEND_H

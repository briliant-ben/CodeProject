#ifndef SCRIPTWORKER_H
#define SCRIPTWORKER_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

class SerialCom;

class ScriptWorker : public QThread
{
    Q_OBJECT

public:
    ScriptWorker(QObject *parent = nullptr);
    ~ScriptWorker() override;
    void transaction(const QString&, SerialCom*);

signals:
    void sendcmd(const QString &);
    void error(const QString &);

private:
    void run() override;
    bool m_quit = false;
    QMutex m_mutex;
    QWaitCondition m_cond;
    QString m_file;
    SerialCom *m_serial= nullptr;
};

#endif // SCRIPTWORKER_H

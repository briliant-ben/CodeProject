#ifndef SERIALLOG_H
#define SERIALLOG_H

#include <QObject>

class QDir;
class QFile;
class QTextStream;
class QTimer;
class QMutex;

class SerialLog : public QObject
{
    Q_OBJECT
public:
    explicit SerialLog(QObject *parent = nullptr, int interval = 10, int filesize = (1<<20));
    ~SerialLog();
    QString getDefaultLogPath();
    bool startRecord(QString, const QString&, bool);
    bool stopRecord();
    static QString preLogPath;

signals:

public slots:
    void recordingLog(const QString&);
    void logFileControl();

private:
    int       updateInterval;
    int       updateFileSize;
    QString         m_prefix;
    QString   defaultLogPath;
    QString  currentPathTemp;
    QDir            *logPath = nullptr;
    QFile           *logFile = nullptr;
    QTextStream *writeStream = nullptr;
    QTimer            *timer = nullptr;
    QMutex          *m_mutex = nullptr;
};

#endif // SERIALLOG_H

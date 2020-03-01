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
    bool startRecord(const QString&, const QString&);
    bool stopRecord();

signals:

public slots:
    void recordingLog(const QString&);
    void logFileControl();

private:
    QString defaultLogPath;
    QString currentPathTemp;
    QString m_prefix;
    QDir *logPath = nullptr;
    QFile *logFile = nullptr;
    QTextStream *writeStream = nullptr;
    QTimer *timer = nullptr;
    QMutex *m_mutex = nullptr;
    int updateInterval;
    int updateFileSize;
};

#endif // SERIALLOG_H

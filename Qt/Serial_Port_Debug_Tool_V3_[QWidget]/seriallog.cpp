#include <QDateTime>
#include <QDir>
#include <QTextStream>
#include <QTimer>
#include <QFileInfo>
#include <QMutex>
//#include <QDebug>
#include "seriallog.h"

SerialLog::SerialLog(QObject *parent, int interval, int filesize) :
    QObject(parent),
    updateInterval(interval),
    updateFileSize(filesize)
{
    currentPathTemp = QDir::current().absolutePath();

    defaultLogPath = "Logs";
    if(!QDir(defaultLogPath).exists())
        QDir::current().mkdir(defaultLogPath);
    defaultLogPath = QDir(defaultLogPath).absolutePath();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(logFileControl()));

    m_mutex = new QMutex();
}

SerialLog::~SerialLog()
{
    delete m_mutex;
    delete timer;
}

QString SerialLog::getDefaultLogPath()
{
    return defaultLogPath;
}

bool SerialLog::startRecord(const QString& path, const QString& prefix)
{
    logPath = new QDir(path);
    if(prefix.size() == 0 || prefix.isNull())
        m_prefix = "Prefix";

    if(!logPath->exists() && !logPath->mkpath(path)){
        delete logPath;
        return false;
    }

    if(!logPath->setCurrent(path)){
        delete logPath;
        return false;
    }

    QDateTime datetime = QDateTime(QDate::currentDate(), QTime::currentTime());
    logFile = new QFile(m_prefix + "_" + datetime.toString("yyyy-MM-dd-hh-mm-ss") + ".txt");
    if (!logFile->open(QIODevice::WriteOnly | QIODevice::Text)){
        delete logPath;
        delete logFile;
        return false;
    }
    writeStream = new QTextStream(logFile);
    timer->start(updateInterval*1000);
    return true;
}

bool SerialLog::stopRecord()
{
    timer->stop();
    logPath->setCurrent(currentPathTemp);
    delete logPath;

    m_mutex->lock();
    logFile->close();
    delete writeStream;
    delete logFile;
    m_mutex->unlock();

    return true;
}

void SerialLog::recordingLog(const QString& data)
{
    static QByteArray array;
    static char flag = 0;
    if(data.contains('\n')){
        flag = 1;
        array.append(data.section('\n', 0, 0));

        m_mutex->lock();
        //(*witeStream) << QTime::currentTime().toString("hh-mm-ss-zzz") << " " << data;
        (*writeStream) << array;
        m_mutex->unlock();
    }else{
        array.append(data);
    }

    if(flag){
        flag = 0;
        array.clear();
        array.append(data.section('\n', 1));
    }
}

void SerialLog::logFileControl()
{
    QFileInfo fi(*logFile);
    if(fi.exists() && fi.size() > updateFileSize){
        QDateTime datetime = QDateTime(QDate::currentDate(), QTime::currentTime());
        QFile *templogFile = new QFile(m_prefix + "_" + datetime.toString("yyyy-MM-dd-hh-mm-ss") + ".txt");
        if (!templogFile->open(QIODevice::WriteOnly | QIODevice::Text)){
            delete templogFile;
            return;
        }
        m_mutex->lock();
        writeStream->flush();
        logFile->close();
        delete logFile;
        logFile = templogFile;
        delete writeStream;
        writeStream = new QTextStream(logFile);
        m_mutex->unlock();
    }else{
        writeStream->flush();
    }
}

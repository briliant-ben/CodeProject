#include <QDateTime>
#include <QDir>
#include <QTextStream>
#include <QTimer>
#include <QFileInfo>
#include <QMutex>
#include "seriallog.h"
//#include <QDebug>

QString SerialLog::preLogPath = "";

SerialLog::SerialLog(QObject *parent, int interval, int filesize) :
    QObject(parent),
    updateInterval(interval),
    updateFileSize(filesize)
{
    currentPathTemp = QDir::current().absolutePath();

    defaultLogPath = "Logs";
    if(!QDir(defaultLogPath).exists())
        QDir::current().mkdir(defaultLogPath);
    preLogPath = defaultLogPath = QDir(defaultLogPath).absolutePath();

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

bool SerialLog::startRecord(QString path, const QString& prefix, bool needpackage)
{
    QDateTime datetime = QDateTime(QDate::currentDate(), QTime::currentTime());

    if(needpackage)
        path.append("\\").append("RealTek_Serial_Log-").append(datetime.toString("yyyy_MM_dd_hh_mm_ss"));

    if(prefix.size() == 0 || prefix.isNull())
        m_prefix = "Prefix";

    logPath = new QDir(path);
    if(!logPath->exists() && !logPath->mkpath(path)){
        delete logPath;
        return false;
    }

    preLogPath = logPath->absolutePath();

    if(!logPath->setCurrent(path)){
        delete logPath;
        return false;
    }

    datetime = QDateTime(QDate::currentDate(), QTime::currentTime());
    logFile = new QFile(m_prefix + "-" + datetime.toString("yyyy_MM_dd_hh_mm_ss") + ".txt");
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
    writeStream->flush();
    logFile->close();
    delete writeStream;
    delete logFile;
    m_mutex->unlock();

    return true;
}

void SerialLog::recordingLog(const QString& data)
{
    static QByteArray array;
    int enternum = data.count('\n');
    int index;
    if(enternum > 0){
        m_mutex->lock();
        (*writeStream) << "[" << QTime::currentTime().toString("hh:mm:ss:zzz").append("] ") << array << data.section('\n', 0, 0) << '\n';
        m_mutex->unlock();
        array.clear();

        for(index = 1; index < enternum; index++){
            m_mutex->lock();
            (*writeStream) << "[" << QTime::currentTime().toString("hh:mm:ss:zzz").append("] ") << data.section('\n', index, index) << '\n';
            m_mutex->unlock();
        }

        array.append(data.section('\n', enternum, enternum));
    }else{
        array.append(data);
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

#include <QDir>
#include <QTextStream>
#include <QTimer>
#include "serialcom.h"
#include "scriptworker.h"
//#include <QDebug>

ScriptWorker::ScriptWorker(QObject *parent):
    QThread(parent)
{
}

ScriptWorker::~ScriptWorker()
{
    m_mutex.lock();
    m_quit = true;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}

void ScriptWorker::transaction(const QString& filepath, SerialCom* serial)
{
    if (!isRunning())
        start();

    const QMutexLocker locker(&m_mutex);
    m_file = filepath;
    m_serial = serial;

    m_cond.wakeOne();
}

void ScriptWorker::run()
{
    QFile *scriptFile;
    QTextStream *readStream;

    while(1){
        m_mutex.lock();
        m_cond.wait(&m_mutex);
        QString file = m_file;
        SerialCom* serial = m_serial;
        m_mutex.unlock();

        if(m_quit)
            break;

        if(false == serial->connectStatus()){
            emit error("Serial Port is NOT Open!");
            break;
        }

        scriptFile = new QFile(file);
        if (!scriptFile->open(QIODevice::ReadOnly | QIODevice::Text)){
            emit error("Open Script File Failed!");
            delete scriptFile;
            continue;
        }

        readStream = new QTextStream(scriptFile);
        while(1){
            QString line = readStream->readLine();
            if(line.isNull() || !line.contains('#')){
                emit error("Script File Format is Wrong!");
                delete readStream;
                scriptFile->close();
                delete scriptFile;
                break;
            }

            int sec = line.section('#', 0, 0).toInt();
            if(sec < 0 || sec > 60){
                emit error("Time in Script File is Wrong!");
                delete readStream;
                scriptFile->close();
                delete scriptFile;
                break;
            }

            emit sendcmd(line.section('#', 1, 1) + "\r"); //serial->incomingWriteData(line.section('#', 1, 1) + "\r");
            sleep(static_cast<unsigned long>(sec));
        }
    }
}

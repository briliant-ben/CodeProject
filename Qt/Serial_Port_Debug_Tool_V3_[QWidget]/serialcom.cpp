#include <QSerialPort>
#include <QSerialPortInfo>
#include "serialcom.h"
#include <QDebug>

SerialCom::SerialCom(QObject *parent) :
    QObject(parent),
    m_serial(new QSerialPort(this))
{
    m_connectStatus = false;
    QObject::connect(m_serial, SIGNAL(readyRead()), this, SLOT(incomingReadData()));
}

SerialCom::~SerialCom()
{
    delete m_serial;
}

QStringList SerialCom::getPortNames()
{
    QStringList portnames;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        portnames << info.portName();
    }
    return portnames;
}

QString SerialCom::getPortInfo(const QString& portname)
{
    QString portinfo;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        if(0 == QString::compare(portname, info.portName())){
            portinfo = tr("Location: ") + info.systemLocation() +
                    "<br/>" + tr("Description: ") + info.description() +
                    "<br/>" + tr("Manufacturer: ") + info.manufacturer() +
                    "<br/>" + tr("Serial number: ") + info.serialNumber() +
                    "<br/>" + tr("Vendor Identifier: ") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) +
                    "<br/>" + tr("Product Identifier: ") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) +
                    "<br/>" + tr("Busy: ") + (info.isBusy() ? ("Yes") : ("No"));
            break;
        }
    }
    if(portinfo.isNull())
        return tr("ERROR: NO PORT AVAILABLE!");
    return portinfo;
}

bool SerialCom::connect(SerialConfig& config)
{
    m_serial->setPortName(config.portname);
    m_serial->setBaudRate(config.speed);
    m_serial->setDataBits(QSerialPort::DataBits(config.databits));
    m_serial->setParity(QSerialPort::Parity(config.parity));
    m_serial->setStopBits(QSerialPort::StopBits(config.stopbits));
    m_serial->setFlowControl(QSerialPort::FlowControl(config.flowcontrol));

    if (m_serial->open(QIODevice::ReadWrite)) {
        m_connectStatus = true;
        emit serialstatus(tr("Connected to # Port: %1 BaudRate: %2 DataBits: %3 Parity: %4 StopBits: %5 FlowControl: %6")
                          .arg(config.portname).arg(config.speed).arg(config.databits)
                          .arg(config.parity).arg(config.stopbits).arg(config.flowcontrol));
        return true;
    } else {
        emit serialstatus(tr("Open Error: ") + m_serial->errorString());
        if(m_serial->error() == QSerialPort::OpenError)
            return true;
        return false;
    }
}

bool SerialCom::disconnect(){
    m_serial->close();
    m_connectStatus = false;
    emit serialstatus(tr("Connetiong Closed."));
    return true;
}

bool SerialCom::connectStatus()
{
    return m_connectStatus;
}

void SerialCom::incomingWriteData(const QString& data)
{
    if(m_connectStatus)
        m_serial->write(data.toLocal8Bit());
}

void SerialCom::incomingReadData()
{
    emit serialReadData(QString(m_serial->readAll()));
}



#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <QObject>

class QSerialPort;

struct SerialConfig{
    QString portname;
    int speed;
    int databits;
    int stopbits;
    int parity;
    int flowcontrol;
};

class SerialCom : public QObject
{
    Q_OBJECT
public:
    explicit SerialCom(QObject *parent = nullptr);
    ~SerialCom();
    QStringList getPortNames();
    QString getPortInfo(const QString& portname);
    bool connect(SerialConfig& config);
    bool disconnect();
    bool connectStatus();

signals:
    void serialReadData(const QString&);
    void serialstatus(const QString&);

public slots:
    void incomingWriteData(const QString&);

private slots:
    void incomingReadData();

private:
    bool m_connectStatus = false;
    QSerialPort *m_serial = nullptr;
};

#endif // SERIALCOM_H

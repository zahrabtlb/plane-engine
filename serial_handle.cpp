#include "serial_handle.h"



SerialWorker::SerialWorker(const QString &portName, QString baudRate, QString parity, QString stopBit , QObject *parent)
    : QObject(parent), serial(new QSerialPort(this)) {

    int baudRate_ = baudRate.toInt();
    QSerialPort::Parity parity_ =  QSerialPort::OddParity;

    if (parity == "NoParity") {
        parity_ = QSerialPort::NoParity;
    } else if (parity == "Even") {
        parity_ = QSerialPort::EvenParity;
    } else if (parity == "Odd") {
        parity_ = QSerialPort::OddParity;
    } else {

        // Handle invalid input
    }

    QSerialPort::StopBits stopBits = QSerialPort::OneStop;

    if (stopBit == "OneStop") {
        stopBits = QSerialPort::OneStop;
    } else if (stopBit == "TwoStop") {
        stopBits = QSerialPort::TwoStop;
    } else {
        // Handle invalid input
    }

    serial->setPortName(portName);
    serial->setBaudRate(baudRate_);
    serial->setParity(parity_);
    serial->setStopBits(stopBits);
    serial->setDataBits(QSerialPort::Data8);
    serial->setFlowControl(QSerialPort::NoFlowControl);
}

SerialWorker::~SerialWorker()
{
       if (serial->isOpen()) {
           serial->close();
       }
}

void SerialWorker::startReading()
{
    if (serial->open(QIODevice::ReadOnly)) {
        while (true) {
            readData();
            QThread::sleep(20); // Sleep for 20 milliseconds
        }
    }
}

void SerialWorker::readData()
{
       if (serial->waitForReadyRead(20)) { // Wait for data to be available
           QByteArray data = serial->readAll();
           processData(data);
       }
}

void SerialWorker::processData(const QByteArray &data)
{
    {
           static QByteArray buffer;
           buffer.append(data);

           while (true) {
               int headerIndex = buffer.indexOf(QByteArray::fromHex("A5A5A5A5"));
               int footerIndex = buffer.indexOf(QByteArray::fromHex("55"));

               if (headerIndex == -1 || footerIndex == -1) {
                   break; // Wait for more data if header or footer is not found
               }

               QByteArray message = buffer.mid(headerIndex, footerIndex - headerIndex + 1);
               processMessage(message);

               buffer.remove(0, footerIndex + 1); // Remove processed message from buffer
           }
    }
}

void SerialWorker::processMessage(const QByteArray &message)
{

}

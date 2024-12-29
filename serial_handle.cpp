#include "serial_handle.h"
#include <QDebug>
#include <QMap>




SerialWorker::SerialWorker(const QString &portName, QString baudRate, QString parity, QString stopBit, QString fileName)
    : serial(new QSerialPort(this)), file(fileName)  {


    openFile(fileName);
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
    MSGCounter = 0;
    stopRequest = 0;

}

SerialWorker::~SerialWorker()
{
    if (serial->isOpen()) {
        serial->close();
    }
    file.close();
}

void SerialWorker::startReading()
{

    if (serial->open(QIODevice::ReadOnly)) {
        while (!stopRequest) {//serial->isOpen()?
            readData();
            //            qDebug() << "sleep\n";
            QThread::msleep(20);


        }
    }
}

void SerialWorker::saveData(QString messageCounter, const QString arr[], int size)
{
    QTextStream out(&file);

    out << messageCounter << ", ";
    for (int i=0; i<size; i++) {
        out << arr[i] << ", ";
    }
    out << "\n";
}

void SerialWorker::openFile(QString fileName)
{
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw std::runtime_error("Failed to open file for writing: " + fileName.toStdString());
    }

    saveData("Message Counter", dataFormat.getDataLabels());
}

void SerialWorker::readData()
{
    if (serial->waitForReadyRead(20)) {
        QByteArray data = serial->readAll();
        processData(data);
    }
}

void SerialWorker::processData(const QByteArray &data)
{

    //    qDebug() << "process data\n";
    buffer.append(data);
    int headerIndex = buffer.indexOf(QByteArray::fromHex("A5A5A5A5"));
    int footerIndex = buffer.indexOf(QByteArray::fromHex("55"));

    while (headerIndex != -1 && footerIndex != -1) {



        QByteArray message = buffer.mid(headerIndex, footerIndex - headerIndex + 1);


        buffer.remove(0, footerIndex + 1); // Remove processed message from buffer


        headerIndex = buffer.indexOf(QByteArray::fromHex("A5A5A5A5"));
        footerIndex = buffer.indexOf(QByteArray::fromHex("55"));
        bool showInGraphics = (headerIndex == -1 || footerIndex == -1);
        processMessage(message, showInGraphics);
    }
    if(headerIndex == -1){
        buffer.clear();
    }

}


void SerialWorker::processMessage(const QByteArray &rawMessage, bool show)
{

    unsigned int messageCounter = extractLittleEndianUInt(rawMessage, 4, 4);
    if(messageCounter == MSGCounter -1){
        //repeated message => ignore
        return;
    }
    MSGCounter = messageCounter + 1;
    unsigned int idNumber = extractLittleEndianUInt(rawMessage, 5, 5);
    int expectedLenght = 9 + (10 * idNumber);
    if(expectedLenght != rawMessage.length()){
        //problem
        return;
    }
    unsigned int checksum = extractLittleEndianUInt(rawMessage, 10 * idNumber + 6, 10 * idNumber + 7);
    if(checksum != calculateChecksum(rawMessage, 5, 10 * idNumber + 5)){
        //broken message
        return;
    }
    QString extracted[30];

    QMap<int,double>* extractedData = new QMap<int, double>;
    for(unsigned int i=0; i<idNumber; i++){
        unsigned int id = extractLittleEndianUInt(rawMessage, 6 + 10 * i, 6 + 10 * i);
        //        unsigned int reserve = extractLittleEndianUInt(message, 7 + 10 * i, 7 + 10 * i);
        unsigned int data = extractLittleEndianUInt(rawMessage, 8 + 10 * i, 11 + 10 * i);
        unsigned int factor = extractLittleEndianUInt(rawMessage, 12 + 10 * i, 15 + 10 * i);
        if(factor == 0) factor = 1;
        double realData = (double)data/factor;
        if(dataFormat.isValid(id, realData)){
            (*extractedData)[id] = realData;
            if(id<0x10){
                extracted[id - 0x01] = QString::number(realData, 'f', 4);
            }
            else{
                extracted[id - 0x02] = QString::number(realData, 'f', 0);
            }
        }

    }
    if(!extractedData->empty()){
        if(show){
            emit messageReceived(extractedData);
        }
        saveData(QString::number(messageCounter), extracted);
    }

}

void SerialWorker::run()
{
    startReading();
}

void SerialWorker::stopLoop()
{
    stopRequest = 1;
}


unsigned int SerialWorker::calculateChecksum(const QByteArray& byteArray, int startIndex, int endIndex) {
    if (startIndex < 0 || endIndex >= byteArray.size() || startIndex > endIndex) {
        throw std::out_of_range("Invalid index range");
    }

    unsigned int checksum = 0;
    for (int i = startIndex; i <= endIndex; ++i) {
        checksum += static_cast<quint8>(byteArray[i]);
    }
    return checksum;
}


unsigned int SerialWorker::extractLittleEndianUInt(const QByteArray& byteArray, int startIndex, int endIndex) {
    if (startIndex < 0 || endIndex >= byteArray.size() || startIndex > endIndex) {
        throw std::out_of_range("Invalid index range");
    }

    // Ensure that at most 4 bytes are processed
    if (endIndex - startIndex >= 4) {
        throw std::invalid_argument("Maximum range for indices is 4 bytes");
    }

    unsigned int result = 0;
    for (int i = startIndex; i <= endIndex; ++i) {
        result |= (static_cast<unsigned char>(byteArray[i]) << ((i - startIndex) * 8));
    }

    return result;
}

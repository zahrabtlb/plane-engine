#include <QThread>
#include <QSerialPort>
#include <QByteArray>
#include "datahandle.h"
#include <QFile>

class SerialWorker : public QThread {
    Q_OBJECT

public:
    SerialWorker(const QString &portName, QString baudRate, QString parity, QString stopBit, QString fileName);

    ~SerialWorker();



private:
    void readData();

    void processData(const QByteArray &data);

    unsigned int calculateChecksum(const QByteArray& byteArray, int startIndex, int endIndex);
    unsigned int extractLittleEndianUInt(const QByteArray& byteArray, int startIndex, int endIndex);

    void processMessage(const QByteArray &rawMessage, bool show);
    void startReading();
    void saveData(QString messageCounter, const QString arr[], int size=30);
    void openFile(QString filename);


signals:
    void messageReceived(QMap<int, double>* message);

private:
    QSerialPort *serial;
    unsigned int MSGCounter;
    dataHandle dataFormat;
    bool stopRequest;
    QByteArray buffer;
    QFile file;

protected:
    void run() override;

public slots:
    void stopLoop();

};

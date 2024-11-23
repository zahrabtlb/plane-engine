#include <QThread>
#include <QSerialPort>
#include <QByteArray>

class SerialWorker : public QObject {
    Q_OBJECT

public:
    SerialWorker(const QString &portName, QString baudRate, QString parity, QString stopBit , QObject *parent = nullptr);

    ~SerialWorker();

public slots:
    void startReading();

private:
    void readData();

    void processData(const QByteArray &data);

    void processMessage(const QByteArray &message);

signals:
    void messageReceived(const QByteArray &message);

private:
    QSerialPort *serial;
};

#ifndef SENSITIVE_DATA_H
#define SENSITIVE_DATA_H

#include <QMainWindow>
#include "gauge.h"
#include "lamp.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QMap>


namespace Ui {
class sensitive_data;
}

class sensitive_data : public QMainWindow
{
    Q_OBJECT

public:
    explicit sensitive_data(QWidget *parent = nullptr);
    ~sensitive_data();

private slots:
    void on_change_clicked();

    void on_stop_clicked();

    void on_close_clicked();

public slots:
    void handleMessage(QMap<int, double>* message);
    void stopSlot();

signals:
    void change();
    void stop();
    void closed();

private:
    Ui::sensitive_data *ui;
    CircularGauge* gaugeOilPressure;
    CircularGauge* gaugeOilTemp;
    CircularGauge* gaugeFuel;
    CircularGauge* gaugeTorque;
    CircularGauge* gaugeMotorSpeed;
    bool error;
    bool errorcheck[15];
    double oilPressure;
    double oilTemperature;
    double fuel;
    double torque;
    double motorSpeed;

    int oilPressureID;
    int oilTemperatureID;
    int fuelID;
    int torqueID;
    int motorSpeedID;


    Lamp* lamp;

};

#endif // SENSITIVE_DATA_H

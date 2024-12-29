#include "sensitive_data.h"
#include "ui_sensitive_data.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include "datahandle.h"

sensitive_data::sensitive_data(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sensitive_data)
{

    ui->setupUi(this);
    ui->close->hide();

    error = false;
    gaugeOilPressure = new CircularGauge(0, 1000);
    gaugeOilPressure->setMajorTickDifference(100);
    gaugeOilTemp = new CircularGauge(0, 400);
    gaugeOilTemp->setMajorTickDifference(50);
    gaugeFuel = new CircularGauge(0, 800);
    gaugeFuel->setMajorTickDifference(100);
    gaugeTorque = new CircularGauge(0, 400);
    gaugeTorque->setMajorTickDifference(50);
    gaugeMotorSpeed = new CircularGauge(0, 1000);
    gaugeMotorSpeed->setMajorTickDifference(100);

    QString style = "color: rgb(220, 0, 0); font-size:15px;";
    QLabel* oilPress = new QLabel("Oil pressure");
    oilPress->setStyleSheet(style);
    oilPress->setAlignment(Qt::AlignCenter);
    QLabel* oilTemp = new QLabel("Oil Temperature");
    oilTemp->setStyleSheet(style);
    oilTemp->setAlignment(Qt::AlignCenter);
    QLabel* fuell = new QLabel("Fuel");
    fuell->setStyleSheet(style);
    fuell->setAlignment(Qt::AlignCenter);
    QLabel* torq = new QLabel("Torque");
    torq->setStyleSheet(style);
    torq->setAlignment(Qt::AlignCenter);
    QLabel* motorsp = new QLabel("Motor Speed");
    motorsp->setStyleSheet(style);
    motorsp->setAlignment(Qt::AlignCenter);

    ui->layout1->addWidget(gaugeOilPressure,10);
    ui->layout1->addWidget(oilPress,1);
    ui->layout2->addWidget(gaugeOilTemp,10);
    ui->layout2->addWidget(oilTemp,1);
    ui->layout3->addWidget(gaugeFuel,10);
    ui->layout3->addWidget(fuell,1);
    ui->layout4->addWidget(gaugeTorque,10);
    ui->layout4->addWidget(torq,1);
    ui->layout5->addWidget(gaugeMotorSpeed,10);
    ui->layout5->addWidget(motorsp,1);

    lamp = new Lamp(this);

    ui->layout6->addWidget(lamp);

    oilPressure = 0.0;
    oilTemperature = 0.0;
    fuel = 0.0;
    torque = 0.0;
    motorSpeed = 0.0;

    oilPressureID = 0x01;
    oilTemperatureID = 0x02;
    fuelID = 0x04;
    torqueID = 0x06;
    motorSpeedID = 0x0B;

    for(int i=0;i<15;i++){
        errorcheck[i] = 0;
    }

}

sensitive_data::~sensitive_data()
{
    delete ui;
}

void sensitive_data::on_change_clicked()
{
    emit change();
}

void sensitive_data::handleMessage(QMap<int, double>* message)
{

    if(message->find(oilPressureID) != message->end()){
        double temp = (*message)[oilPressureID];
        if(temp != oilPressure){
            oilPressure = temp;
            gaugeOilPressure->setValue(temp);
        }
    }
    if(message->find(oilTemperatureID) != message->end()){
        double temp = (*message)[oilTemperatureID];
        if(temp != oilTemperature){
            oilTemperature = temp;
            gaugeOilTemp->setValue(temp);
        }
    }
    if(message->find(fuelID) != message->end()){
        double temp = (*message)[fuelID];
        if(temp != fuel){
            fuel = temp;
            gaugeFuel->setValue(temp);
        }
    }
    if(message->find(torqueID) != message->end()){
        double temp = (*message)[torqueID];
        if(temp != torque){
            torque = temp;
            gaugeTorque->setValue(temp);
        }
    }
    if(message->find(motorSpeedID) != message->end()){
        double temp = (*message)[motorSpeedID];
        if(temp != motorSpeed){
            motorSpeed = temp;
            gaugeMotorSpeed->setValue(temp);
        }
    }
    bool checkError = false;
    for(int i = 0x11;i<=0x1F;i++){
        if(message->find(i) != message->end()){

            errorcheck[i - 0x11] = ((*message)[i] == 1);

        }
        checkError = checkError || errorcheck[i - 0x11];
    }
    error = checkError;

    lamp->changeError(error);

    delete message;
}

void sensitive_data::stopSlot()
{
    ui->stop->hide();
    ui->close->show();
}

void sensitive_data::on_stop_clicked()
{
    ui->stop->hide();
    ui->close->show();
    emit stop();
}

void sensitive_data::on_close_clicked()
{
    emit closed();
}

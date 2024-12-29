#include "datahandle.h"

dataHandle::Data::Data(int id, QString dataLabel, int min, int max)
    : id(id), dataLabel(dataLabel), min(min), max(max){}


dataHandle::dataHandle()
{
    dataLabels[0] = "OIL PRESSURE";
    dataLabels[1] = "OIL TEMPERATURE";
    dataLabels[2] = "FUEL FLOW";
    dataLabels[3] = "FUEL";
    dataLabels[4] = "EGT";
    dataLabels[5] = "TORQUE";
    dataLabels[6] = "INDICATED POWER";
    dataLabels[7] = "Frictional Power";
    dataLabels[8] = "Thermal efficiency";
    dataLabels[9] = "Air-Fuel ratio";
    dataLabels[10] = "MOTOR SPEED";
    dataLabels[11] = "OUTPUT AIR SPEED";
    dataLabels[12] = "VIBRATION";
    dataLabels[13] = "BODY TEMP";
    dataLabels[14] = "AIR TEMP";
    for(int i=15;i<30;i++){
        dataLabels[i] = dataLabels[i-15] + " SENSOR";
    }
    datas[0x01] = new Data(0x01, dataLabels[0] , 0, 1000);
    datas[0x02] = new Data(0x02, dataLabels[1] , 0, 400);
    datas[0x03] = new Data(0x03, dataLabels[2] , 0, 800);
    datas[0x04] = new Data(0x04, dataLabels[3] , 0, 800);
    datas[0x05] = new Data(0x05, dataLabels[4] , 0, 400);
    datas[0x06] = new Data(0x06, dataLabels[5] , 0, 400);
    datas[0x07] = new Data(0x07, dataLabels[6] , 0, 400);
    datas[0x08] = new Data(0x08, dataLabels[7] , 0, 400);
    datas[0x09] = new Data(0x09, dataLabels[8] , 0, 100);
    datas[0x0A] = new Data(0x0A, dataLabels[9] , 0, 20);
    datas[0x0B] = new Data(0x0B, dataLabels[10], 0, 1000);
    datas[0x0C] = new Data(0x0C, dataLabels[11], 0, 1000);
    datas[0x0D] = new Data(0x0D, dataLabels[12], 0, 100);
    datas[0x0E] = new Data(0x0E, dataLabels[13], 0, 400);
    datas[0x0F] = new Data(0x0F, dataLabels[14], 0, 400);

    datas[0x11] = new Data(0x11, dataLabels[15], 0, 1);
    datas[0x12] = new Data(0x12, dataLabels[16], 0, 1);
    datas[0x13] = new Data(0x13, dataLabels[17], 0, 1);
    datas[0x14] = new Data(0x14, dataLabels[18], 0, 1);
    datas[0x15] = new Data(0x15, dataLabels[19], 0, 1);
    datas[0x16] = new Data(0x16, dataLabels[20], 0, 1);
    datas[0x17] = new Data(0x17, dataLabels[21], 0, 1);
    datas[0x18] = new Data(0x18, dataLabels[22], 0, 1);
    datas[0x19] = new Data(0x19, dataLabels[23], 0, 1);
    datas[0x1A] = new Data(0x1A, dataLabels[24], 0, 1);
    datas[0x1B] = new Data(0x1B, dataLabels[25], 0, 1);
    datas[0x1C] = new Data(0x1C, dataLabels[26], 0, 1);
    datas[0x1D] = new Data(0x1D, dataLabels[27], 0, 1);
    datas[0x1E] = new Data(0x1E, dataLabels[28], 0, 1);
    datas[0x1F] = new Data(0x1F, dataLabels[29], 0, 1);

    dataLabels[0] = "OIL PRESSURE";
    dataLabels[1] = "OIL TEMPERATURE";
    dataLabels[2] = "FUEL FLOW";
    dataLabels[3] = "FUEL";
    dataLabels[4] = "EGT";
    dataLabels[5] = "TORQUE";
    dataLabels[6] = "INDICATED POWER";
    dataLabels[7] = "Frictional Power";
    dataLabels[8] = "Thermal efficiency";
    dataLabels[9] = "Air-Fuel ratio";
    dataLabels[10] = "MOTOR SPEED";
    dataLabels[11] = "OUTPUT AIR SPEED";
    dataLabels[12] = "VIBRATION";
    dataLabels[13] = "BODY TEMP";
    dataLabels[14] = "AIR TEMP";
    for(int i=15;i<30;i++){
        dataLabels[i] = dataLabels[i-15] + " SENSOR";
    }
}

bool dataHandle::isValid(int dataID, double value)
{
    if(dataID >= 0x01 && dataID <= 0x0F){
        if(datas[dataID]->max < value || datas[dataID]->min > value){
            return false;
        }
        return true;
    }
    else if(dataID >= 0x11 && dataID <= 0x1F){
        if(value == 0 || value == 1) return true;

    }
    return false;
}

const QString *dataHandle::getDataLabels()
{
    return dataLabels;
}

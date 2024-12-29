#ifndef DATAHANDLE_H
#define DATAHANDLE_H

#include <QMap>

class dataHandle
{

    struct Data{
        int id;
        QString dataLabel;
        int min;
        int max;
        double value;
        Data(int id, QString dataLabel, int min, int max);
    };
    QString dataLabels[30];

public:
    QMap<int, Data*> datas;
    dataHandle();
    bool isValid(int dataID, double value);
    const QString *getDataLabels();

};



#endif // DATAHANDLE_H

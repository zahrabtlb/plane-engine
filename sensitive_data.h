#ifndef SENSITIVE_DATA_H
#define SENSITIVE_DATA_H

#include <QMainWindow>
#include "gauge.h"


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

signals:
    void change();

private:
    Ui::sensitive_data *ui;
    CircularGauge* g;
};

#endif // SENSITIVE_DATA_H

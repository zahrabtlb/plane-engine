#include "all_data.h"
#include "ui_all_data.h"

all_data::all_data(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::all_data)
{
    ui->setupUi(this);
    for(int i=0;i<15;i++){
        errors[i] = new QListWidgetItem("0");
        values[i] = new QListWidgetItem("0");
        ui->list1->addItem(errors[i]);
        ui->list2->addItem(values[i]);
    }
    ui->close->hide();

}

all_data::~all_data()
{
    delete ui;
}

void all_data::on_change_clicked()
{
    emit change();
}

void all_data::handleMessage(QMap<int, double> *message)
{
    for(auto it=message->begin(); it!=message->end(); it++){
        if(it.key()<0x10){
            values[it.key()-0x01]->setText(QString::number(it.value(), 'f', 4));
        }
        else{
            errors[it.key()-0x11]->setText(QString::number(it.value(), 'f', 0));
        }
    }
}

void all_data::stopSlot()
{
    ui->stop->hide();
    ui->close->show();
}

void all_data::on_stop_clicked()
{
    ui->stop->hide();
    ui->close->show();
    emit stop();

}

void all_data::on_close_clicked()
{
    emit closed();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_start_clicked()
{

    sensitive = new sensitive_data();
    all = new all_data();

    worker = new SerialWorker(ui->portAddress->text(), ui->baudRate->text(), ui->parity->text(), ui->stopBit->text(), "saved_data.csv");
    worker->start();

    connect(worker, &SerialWorker::messageReceived, sensitive, &sensitive_data::handleMessage);
    connect(worker, &SerialWorker::messageReceived, all, &all_data::handleMessage);


    connect(sensitive, &sensitive_data::stop, this, &MainWindow::stop_serial);
    connect(all, &all_data::stop, this, &MainWindow::stop_serial);
    connect(sensitive, &sensitive_data::closed, this, &MainWindow::back);
    connect(all, &all_data::closed, this, &MainWindow::back);
    connect(sensitive, &sensitive_data::change, this, &MainWindow::show_all);
    connect(all, &all_data::change, this,  &MainWindow::show_sensitive);
    connect(this, &MainWindow::stopSignal, worker,  &SerialWorker::stopLoop);
    connect(this, &MainWindow::stopSignal, sensitive, &sensitive_data::stopSlot);
    connect(this, &MainWindow::stopSignal, all, &all_data::stopSlot);

    sensitive->resize(800, 600);
    all->resize(800, 600);
    all->show();
    all->hide();
    sensitive->show();
    this->hide();

}

void MainWindow::show_sensitive()
{
    sensitive->show();
    all->hide();

}

void MainWindow::show_all()
{
    all->show();
    sensitive->hide();

}

void MainWindow::stop_serial()
{
    emit stopSignal();
}

void MainWindow::back()
{
    all->close();
    delete all;
    sensitive->close();
    delete sensitive;
    delete worker;
    this->show();
}



#include "mainwindow.h"
#include "ui_mainwindow.h"


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

    connect(sensitive, &sensitive_data::change, this, &MainWindow::show_all);
    connect(all, &all_data::change, this,  &MainWindow::show_sensitive);

    sensitive->show();

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



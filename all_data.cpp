#include "all_data.h"
#include "ui_all_data.h"

all_data::all_data(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::all_data)
{
    ui->setupUi(this);
}

all_data::~all_data()
{
    delete ui;
}

void all_data::on_change_clicked()
{
    emit change();
}

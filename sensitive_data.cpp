#include "sensitive_data.h"
#include "ui_sensitive_data.h"

sensitive_data::sensitive_data(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sensitive_data)
{
    ui->setupUi(this);
//    g = new CircularGauge();
//    g->show();
//    QVBoxLayout *layout = new QVBoxLayout(this);

//    HalfCircleGauge *gauge2 = new HalfCircleGauge();

//    layout->addWidget(gauge2);

//    // Set an example value for demonstration
//    gauge2->setValue(75); // Set initial value (75%)
//    gauge2->show();

//    setLayout(layout);
}

sensitive_data::~sensitive_data()
{
    delete ui;
}

void sensitive_data::on_change_clicked()
{
    emit change();
}

#ifndef ALL_DATA_H
#define ALL_DATA_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
class all_data;
}

class all_data : public QMainWindow
{
    Q_OBJECT

public:
    explicit all_data(QWidget *parent = nullptr);
    ~all_data();

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
    Ui::all_data *ui;
    QListWidgetItem* errors[15];
    QListWidgetItem* values[15];
};

#endif // ALL_DATA_H

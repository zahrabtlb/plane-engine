#ifndef ALL_DATA_H
#define ALL_DATA_H

#include <QMainWindow>

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

signals:
    void change();

private:
    Ui::all_data *ui;
};

#endif // ALL_DATA_H

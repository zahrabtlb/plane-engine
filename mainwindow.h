#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sensitive_data.h"
#include "all_data.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_start_clicked();
    void show_sensitive();
    void show_all();

private:
    Ui::MainWindow *ui;
    sensitive_data* sensitive;
    all_data* all;
};
#endif // MAINWINDOW_H

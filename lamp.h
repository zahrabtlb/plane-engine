#ifndef LAMP_H
#define LAMP_H


#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <cmath> // For M_PI
#include <QLabel>

class Lamp : public QWidget {
    Q_OBJECT

public:
    Lamp(QWidget *parent = nullptr);

    void changeError(bool error);


protected:
    void paintEvent(QPaintEvent *event) override;


private:
    bool currentError;


};


#endif // LAMP_H

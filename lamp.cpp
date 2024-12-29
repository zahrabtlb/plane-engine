#include "lamp.h"

Lamp::Lamp(QWidget *parent): QWidget(parent)
{
    currentError = 0;
}

void Lamp::changeError(bool error)
{
    if(currentError != error){
        currentError = error;
        update();
    }
}

void Lamp::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int side = qMin(width(), height());
    QRectF rect(10, 10, side - 10, side - 10);
    painter.setBrush(Qt::green);
    if(currentError){
        painter.setBrush(Qt::red);
    }
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(rect.center(), side/20, side/20);
}

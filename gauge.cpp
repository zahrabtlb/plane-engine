#include "gauge.h"

CircularGauge::CircularGauge( double min, double max, QWidget *parent): QWidget(parent),
      minValue(min), maxValue(max), currentValue(min){

    side = qMin(width(), height());
    side = qMin(side, 280);
    QLinearGradient gradient1(20, 20, side, side);
    gradient = gradient1;
    gradient.setColorAt(0, Qt::yellow);
    gradient.setColorAt(1, Qt::red);
    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    label->setText(QString::number(currentValue));
    majorTickDiff = 10;
    minorTickDiff = 5;
}

void CircularGauge::setRange(double min, double max) {
    minValue = min;
    maxValue = max;
    update();
}

void CircularGauge::setValue(double value)
{
    if(value < minValue)
        currentValue = minValue;
    else if (value > maxValue)
        currentValue = maxValue;
    else
        currentValue = value;
    label->setText(QString::number(value)); // Update label text
    update();
}

void CircularGauge::setMajorTickDifference(double majorTick)
{
    majorTickDiff = majorTick;
    minorTickDiff = majorTickDiff/5;
    update();
}

void CircularGauge::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    side = qMin(width(), height());
    QRectF rect(10, 10, side - 10, side - 10);

    drawGaugeSegments(painter, rect);
    drawTicksAndLabels(painter, rect);
    drawNeedle(painter, rect);

    adjustLabelPosition(rect);
}

void CircularGauge::drawGaugeSegments(QPainter &painter, const QRectF &rect) {

    painter.setBrush(QBrush(gradient));
    painter.setPen(Qt::NoPen);
    side = qMin(width(), height());
    painter.drawEllipse(rect.center(), side/2 - 5, side/2 - 5);
}

void CircularGauge::drawTicksAndLabels(QPainter &painter, const QRectF &rect) {
    painter.setPen(QPen(Qt::white, 3));


    int majorTickCount = (maxValue - minValue)/majorTickDiff;
    int minorTickCount = majorTickCount * 5;

    double angleStep = 270.0 / (majorTickCount);
    double minorAngleStep = 270.0 / minorTickCount;

    // Draw major ticks and labels
    for (int i = 0; i <= majorTickCount; ++i) {
        double angle = 225 - i * angleStep;
        double radians = angle * M_PI / 180.0;

        QPointF innerPoint(rect.center().x() + (rect.width() / 2 - 30) * cos(radians),
                           rect.center().y() - (rect.height() / 2 - 30) * sin(radians));
        QPointF outerPoint(rect.center().x() + (rect.width() / 2 - 15) * cos(radians),
                           rect.center().y() - (rect.height() / 2 - 15) * sin(radians));

        painter.drawLine(innerPoint, outerPoint);

        // Draw labels

        double value = minValue + i * ((maxValue - minValue) / (majorTickCount));
        QPointF labelPoint(rect.center().x() + (rect.width() / 2 - 47) * cos(radians) - 12,
                           rect.center().y() - (rect.height() / 2 - 47) * sin(radians) + 5);
        QFont font = painter.font();
        font.setPointSize(8);
        painter.setFont(font);
        painter.drawText(labelPoint, QString::number(value));
    }

    // Draw minor ticks
    painter.setPen(QPen(Qt::white, 2));
    for (int i = 0; i <= minorTickCount; ++i) {
        double angle = 225 - i * minorAngleStep;
        double radians = angle * M_PI / 180.0;

        QPointF innerPoint(rect.center().x() + (rect.width() / 2 - 25) * cos(radians),
                           rect.center().y() - (rect.height() / 2 - 25) * sin(radians));
        QPointF outerPoint(rect.center().x() + (rect.width() / 2 - 20) * cos(radians),
                           rect.center().y() - (rect.height() / 2 - 20) * sin(radians));

        painter.drawLine(innerPoint, outerPoint);
    }
}

void CircularGauge::drawNeedle(QPainter &painter, const QRectF &rect) {
    double spanAngle = 270.0;
    double valueAngle = 225 - (currentValue - minValue) * spanAngle / (maxValue - minValue);
    double radians = valueAngle * M_PI / 180.0;

    QPointF topPoint(rect.center().x() + (rect.width() / 2 - 60) * cos(radians),
                      rect.center().y() - (rect.height() / 2 - 60) * sin(radians));

    QPointF bottomPoint(rect.center().x() - (20) * cos(radians),
                      rect.center().y() + (20) * sin(radians));



    double halfBaseLength = 2.5;
    double dx = bottomPoint.x() - topPoint.x();
    double dy = bottomPoint.y() - topPoint.y();
    double perpendicularX = -dy / std::sqrt(dx * dx + dy * dy);
    double perpendicularY = dx / std::sqrt(dx * dx + dy * dy);

    QPointF basePoint1(bottomPoint.x() + halfBaseLength * perpendicularX,
                       bottomPoint.y() + halfBaseLength * perpendicularY);
    QPointF basePoint2(bottomPoint.x() - halfBaseLength * perpendicularX,
                       bottomPoint.y() - halfBaseLength * perpendicularY);


    QPointF points[3] = {topPoint, basePoint1, basePoint2};

     painter.setPen(QPen(Qt::white, 0));

     painter.setBrush(Qt::white);


     painter.drawPolygon(points, 3);

    painter.setBrush(Qt::white);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(rect.center(), 6, 6);

}


void CircularGauge::adjustLabelPosition(const QRectF &rect) //rename
{
    QString style = "font-size: ";
    style += QString::number(qMax(5, side/10 - 8));
    style += "px; color: white; background-color: rbga(255, 255, 255, 0);";
    label->setStyleSheet(style);
    int a = rect.center().x()-side/10;
    int b = rect.center().y()+side/3.5;
    label->setGeometry(a, b, side/5, side/10);

}

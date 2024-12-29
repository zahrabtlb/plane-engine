#ifndef GAUGE_H
#define GAUGE_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <cmath> // For M_PI
#include <QLabel>

class CircularGauge : public QWidget {
    Q_OBJECT

public:
    CircularGauge(double min, double max, QWidget *parent = nullptr);

    void setRange(double min, double max);

    void setValue(double value);

    void setMajorTickDifference(double majorTick);



protected:
    void paintEvent(QPaintEvent *event) override;


private:
    double minValue;
    double maxValue;
    double currentValue;
    QLabel* label;
    double majorTickDiff;
    double minorTickDiff;

    QLinearGradient gradient;
    int side; //the lenght and height od widjet

    void drawGaugeSegments(QPainter &painter, const QRectF &rect);

    void drawTicksAndLabels(QPainter &painter, const QRectF &rect);

    void drawNeedle(QPainter &painter, const QRectF &rect);


    // Adjust label geometry in the center bottom of the gauge
    void adjustLabelPosition(const QRectF &rect);
};

#endif

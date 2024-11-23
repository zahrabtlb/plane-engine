
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QVBoxLayout>
#include <QLabel>

class CircularGauge : public QWidget {
    Q_OBJECT

public:
    CircularGauge(QWidget *parent = nullptr) : QWidget(parent), value(0) {}

    void setValue(int newValue) {
        value = newValue;
        update(); // Trigger a repaint
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QRectF rect(10, 10, width() - 20, height() - 20);

        // Draw background circle
        painter.setBrush(Qt::lightGray);
        painter.drawEllipse(rect);

        // Draw the needle
        painter.setPen(QPen(Qt::red, 2));

        double angle = (value / 100.0) * 180; // Assuming value ranges from 0 to 100
        painter.save();
        painter.translate(width() / 2, height() / 2);
        painter.rotate(-90 + angle); // Rotate to point at the value
        painter.drawLine(0, 0, 0, -rect.height() / 2); // Draw the needle
        painter.restore();
    }

private:
    int value; // Current value of the gauge
};




class HalfCircleGauge : public QWidget {
    Q_OBJECT

public:
    HalfCircleGauge(QWidget *parent = nullptr) : QWidget(parent), value(0) {
        setMinimumSize(200, 100); // Set minimum size for the widget
    }

    void setValue(int newValue) {
        value = newValue;
        update(); // Trigger a repaint
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Draw background arc
        QRectF rect(0, 0, width(), height());
        painter.setBrush(Qt::lightGray);
        painter.drawArc(rect, 0 * 16, 180 * 16); // Draw half circle (180 degrees)

        // Draw foreground arc based on value
        painter.setBrush(Qt::green);
        int angle = static_cast<int>(value / 100.0 * 180); // Convert value to angle
        painter.drawArc(rect, 0 * 16, angle * 16); // Draw filled arc

        // Draw needle
        painter.setPen(QPen(Qt::red, 2));
        painter.save();
        painter.translate(width() / 2, height()); // Move to the center bottom of the widget
        painter.rotate(-90 + angle); // Rotate to point at the value
        painter.drawLine(0, 0, 0, -height() / 2); // Draw the needle
        painter.restore();

        // Draw text label (optional)
        painter.drawText(rect, Qt::AlignCenter, QString::number(value) + "%");
    }

private:
    int value; // Current value of the gauge (0-100)
};


//#include "moc_halfcirclegauge.cpp" // Include MOC file for QObject features if needed

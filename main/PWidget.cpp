#include "PWidget.h"

#include <QPainter>
#include <QTime>
#include <cmath>


PendulumWidget::PendulumWidget(QWidget* parent) : QWidget(parent) {
    setStyleSheet("background-color: black;");

    setFixedSize(800, 600);

    time = startTimer(tStep, Qt::PreciseTimer);

    
}

void PendulumWidget::drawPendulum(QPainter& qp) {
    // Pivot point
    int xPivot = 400;
    int yPivot = 100;
    // bob
    int xBob = xPivot + (l * scaleUp) * sinf(theta1);
    int yBob = yPivot + (l * scaleUp) * cosf(theta1);

    QPen pen(Qt::white, 2, Qt::SolidLine);
    qp.setPen(pen);
    qp.drawLine(xPivot, yPivot, xBob, yBob);

    qp.setPen(QColor(255, 0, 0));
    qp.drawEllipse(QPoint(xBob, yBob), 30, 30);
    

}


void PendulumWidget::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);

    QPainter qp(this);
    drawPendulum(qp);
    
}

void PendulumWidget::timerEvent(QTimerEvent* e) {
    Q_UNUSED(e);

    // theta1_0 -= 0.01f;
    double dt = tStep / 1000.0;
    theta1 += theta2 * dt;
    theta2 = theta2 - (b/m * theta2 + g/l * sin(theta1)) * dt;


    repaint(); // Call PaintEvent
}
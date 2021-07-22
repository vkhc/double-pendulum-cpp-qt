#include "pendulum.h"

#include <cmath>


void SinglePendulum::drawPendulum(QPainter& qp) {
    // Pivot point
    int pivotX = 400; // TODO : define this point
    int pivotY = 100; // relative to qp dimensions

    // TODO: better way of scaling up
    // instead of literal 400 below
    int bobX = pivotX + (l * 300) * sinf(theta);
    int bobY = pivotY + (l * 300) * cosf(theta);

    // Draw pendulum
    // TODO: don't create new QPen everytime;
    QPen pen(Qt::white, 2, Qt::SolidLine);
    qp.setPen(pen);
    qp.drawLine(pivotX, pivotY, bobX, bobY);
    
    // Draw bob
    qp.setPen(Qt::red);
    qp.drawEllipse(QPoint(bobX, bobY), 30, 30);
}

void SinglePendulum::stepAdvance(float tStep) {
    float dt = tStep / 1000.0f; // convert to ms
    theta += omega * dt;
    // Use updated theta below
    omega = omega - (b/m * omega + g/l * sinf(theta)) * dt;
}
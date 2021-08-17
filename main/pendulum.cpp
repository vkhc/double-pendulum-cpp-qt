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
    float dt = tStep / 1000.0f; // convert to s
    theta += omega * dt;
    // Use updated theta below
    omega = omega - (b/m * omega + g/l * sinf(theta)) * dt;
}


// TODO : add other solvers as well
void DoublePendulum::stepAdvanceEuler(float tStep) {
    // Euler method produces bad approximation so very small time steps should be used
    double dt = tStep / 1000.0; // Convert to seconds

    double divisor = 2*m1+m2-m2*cos(2*theta1-2*theta2);
    double M = m1 + m2;
    double deltaTheta = theta1 -theta2;

    theta1 += omega1 * dt;
    theta2 += omega2 * dt;

    omega1 = omega1 - 
             (
                g*(2*M)*sin(theta1) +
                m2*g*sin(theta1-2*theta2) +
                2*sin(deltaTheta)*m2*(omega2*omega2*l2+omega1*omega1*l1*cos(deltaTheta))
             ) / (l1 * divisor) * dt;

    omega2 = omega2 +
             (
                 2*sin(deltaTheta)*
                 (
                    omega1*omega1*l1*(M)+g*(M)*cos(theta1) +
                    omega2*omega2*l2*m2*cos(deltaTheta)
                 )
             ) / (l2 * divisor) * dt;

}

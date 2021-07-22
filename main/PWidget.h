#pragma once

#include <QWidget>


class PendulumWidget : public QWidget {
public:
    PendulumWidget(QWidget* parent = nullptr);
    void drawPendulum(QPainter& qp);



protected:
    void paintEvent(QPaintEvent* e) override;
    void timerEvent(QTimerEvent* e) override;


private:
    float m = 1; // Mass of bob [kg]
    float l = 1; // Length of pendulum [m]
    float b = 0.1; // Damping []
    float g = 9.81; // Gravitational acceleration [m/s^2]
    int tStep = 10; // Time step [ms]
    int time;
    float theta1_0 = 3.14/2; // Initial angle
    float theta2_0 = 0; // Initial angular velocity
    float theta2 = theta2_0;
    float theta1 = theta1_0;

    int scaleUp = 300;

};
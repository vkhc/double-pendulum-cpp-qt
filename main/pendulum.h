#ifndef _PENDULUM_H_
#define _PENDULUM_H_

#include <QPainter>




class SinglePendulum {
public:
    void drawPendulum(QPainter& qp);
    void stepAdvance(float tStep);
    

private:
    float g = 9.81; // Gravitational acceleration
    float m = 1; // Mass of bob [kg]
    float l = 1; // Length of pendulum [m]
    float b = 0.3; // Damping []
    float theta0 = 3.14/2; // Initial angle of pendulum
    float omega0 = 0; // Initial angular velocity
    float theta = theta0;
    float omega = omega0;

};




#endif // _PENDULUM_H_

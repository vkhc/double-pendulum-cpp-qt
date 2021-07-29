#ifndef _PENDULUM_H_
#define _PENDULUM_H_

#include <QPainter>


class SinglePendulum {
public:
    void drawPendulum(QPainter& qp);
    void stepAdvance(float tStep);
    

private:
    double g = 9.81; // Gravitational acceleration
    double m = 1; // Mass of bob [kg]
    double l = 1; // Length of pendulum [m]
    double b = 0.3; // Damping []
    double theta0 = 3.14/2; // Initial angle of pendulum
    double omega0 = 0; // Initial angular velocity
    double theta = theta0;
    double omega = omega0;

};

class DoublePendulum {
public:
    void stepAdvanceEuler(float tStep);

    const double getG() const { return g; }
    void setG(double x) {g = x;}

    double getM1()  { return m1; }
    double getL1()  { return l1; }
    double getTheta1()  { return theta1; }
    double getOmega1()  { return omega1;}
    double getM2()  { return m2; }
    double getL2()  { return l2; }
    double getTheta2()  { return theta2; }
    double getOmega2()  { return omega2;}

    void setM1(double x) { m1 = x; }
    void setL1(double x) { l1 = x; }
    void setTheta1(double x) { theta1 = x; }
    void setOmega1 (double x) { omega1 = x;}
    void setM2(double x) { m2 = x; }
    void setL2(double x) { l2 = x; }
    void setTheta2(double x) { theta2 = x; }
    void setOmega2 (double x) { omega2 = x;}

    void addToTheta1 (double angle) { theta1 += angle;}
    void addToTheta2 (double angle) { theta2 += angle;}
    

private:
    double g = 9.80; // Gravitational acceleration
    double m1 = 2; // Mass of first bob [kg]
    double m2 = 2; // Mass of second bob [kg]
    double l1 = 1.0; // Length of the first pendulum [m]
    double l2 = 1.0; // Length of the second pendulum [m]
    double theta1 = 3.14; // Angle of the first pendulum [rad]
    double theta2 = -3.14/2; // Angle of the second pendulum [rad]
    double omega1 = 0; // Angular velocity of the first pendulum [rad/s]
    double omega2 = 0; // Angular velocity of the second pendulum [rad/s]
};




#endif // _PENDULUM_H_

#include "PWidget.h"
#include "helpers.h"

#include <QPainter>
#include <QTime>
#include <cmath>





PendulumWidget::PendulumWidget(QWidget* parent) : QWidget(parent),
                                                  pendulum(new DoublePendulum) {
    // TODO: Orginize stylesheets properly
    setStyleSheet("background-color: black;");
    // TODO: Dynamic screen size?
    setFixedSize(WIDTH, HEIGHT);

    timerId = startTimer(tStep, Qt::PreciseTimer);

    pivot.setX(WIDTH / 2);
    pivot.setY(HEIGHT / 2);

}

void PendulumWidget::drawPendulum(QPainter& qp) {
    double l1 = pendulum->getL1();
    double l2 = pendulum->getL2();
    double theta1 = pendulum->getTheta1();
    double theta2 = pendulum->getTheta2();

    // Set scalefactor so that total length of pendulum is scaled 
    // up to roughly half of the screen
    float scaleFactor = (float)std::min(WIDTH, HEIGHT) / (l1 + l2) * 0.4;

    // Location of bob 1
    bob1.setX(pivot.x() + l1 * sin(theta1) * scaleFactor);
    bob1.setY(pivot.y() + l1 * cos(theta1) * scaleFactor);
    // Location of bob 2
    bob2.setY(bob1.y() + l2 * cos(theta2) * scaleFactor);
    bob2.setX(bob1.x() + l2 * sin(theta2) * scaleFactor);
    // Set bob size according
    int bobRadius = (l1 + l2) / 20 * scaleFactor;
    // Set pendulum rod width

    QPen pen(Qt::gray, 5, Qt::SolidLine);
    qp.setPen(pen);

    qp.drawLine(pivot, bob1); // Pendulum 1
    qp.drawLine(bob1, bob2); // Pendulum 2
    pen.setColor(Qt::red);
    pen.setWidth(1);
    qp.setPen(pen);
    
    // Draw bob 1
    QRadialGradient gradientBob1(bob1.x(), bob1.y(), bobRadius);
    gradientBob1.setColorAt(0.0, Qt::white);
    gradientBob1.setColorAt(1.0, Qt::red);
    qp.setBrush(gradientBob1);
    qp.drawEllipse(bob1, bobRadius, bobRadius);

    // Draw bob 2
    QRadialGradient gradientBob2(bob2.x(), bob2.y(), bobRadius);
    gradientBob2.setColorAt(0.0, Qt::white);
    gradientBob2.setColorAt(1.0, Qt::red);
    qp.setBrush(gradientBob2);
    qp.drawEllipse(bob2, bobRadius, bobRadius);
}

void PendulumWidget::tracePendulum() {
    trace.emplace(trace.begin(), bob2);
    if (trace.size() >= traceLength) trace.pop_back();   
}

void PendulumWidget::drawTrace(QPainter& qp, deque<QPoint> D, QColor color) {
    int tail = traceLength;
    qp.setRenderHint(QPainter::SmoothPixmapTransform, true);
    QPen pen(color, 3);
    qp.setPen(pen);
    QLine line;
    
    int red = color.red();      // Get rgb values of input color
    int green = color.green();  // to use them for fading tail
    int blue = color.blue();    // in the loop below

    int n = 2;  // Every nth point in deque will be connected into a straight line
    for (int i=D.size()-1; i>n+6; i-=n) {   // Iterate in reverse order, so that head of the trace
                                            // is drawn after the tale
                                            // By setting i to more than 0, trace will be behind the ball
        // qp.drawPoint(D[i]);
        line.setP1(D[i]);
        line.setP2(D[i-n]);
        // Add fading tail
        if (i > traceLength - tail) {
            // Function to give 1 at beginning of tail and 0 at the end of the line
            float y = -1.0f / traceLength * (i - (traceLength - tail)) + 1; 

            color.setRed(y * red);      // Reduce RGB values
            color.setGreen(y * green);
            color.setBlue(y * blue);

            pen.setColor(color);
            qp.setPen(pen);
        }
        qp.drawLine(line);
    }
}

void PendulumWidget::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);
    
    QPainter qp(this);
    drawTrace(qp ,trace, Qt::red);
    drawPendulum(qp);  
    
}

void PendulumWidget::timerEvent(QTimerEvent* e) {
    Q_UNUSED(e);
    if (active) {
        tracePendulum();
        // Divide timerEvent interval by reductionFactor to get small enough
        // Time steps for euler methods
        int reductionFactor = 50;
        float t = (float)tStep/reductionFactor;
        // Do numerical approximation reductionFactor times
        for (int i=0; i<reductionFactor; ++i) { //
            pendulum->stepAdvanceEuler(t);
        }
    }
    repaint(); // Call PaintEvent
}

void PendulumWidget::mousePressEvent(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton) {
        last = e->position().toPoint();
        if (doSnap(last, bob1, 50)) {
            mousePressed = true;
            active = false;
            bob1Snaped = true;
        } else if (doSnap(last, bob2, 50)) {
            mousePressed = true;
            active = false;
            bob2Snaped = true;
        }
    }
}

void PendulumWidget::mouseMoveEvent(QMouseEvent* e) {
    if (e->buttons() & Qt::LeftButton && mousePressed) {
        current = e->position().toPoint();
        if (bob1Snaped) moveBob1();
        if (bob2Snaped) moveBob2();

        last = current;

    }
}

void PendulumWidget::mouseReleaseEvent(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton && mousePressed) {

        mousePressed = false;
        active = true;
        bob1Snaped = false;
        bob2Snaped = false;
    }
}

void PendulumWidget::moveBob1(){
        QLine l1(pivot, last);
        QLine l2(pivot, current);
        float dTheta = getAngle(l1, l2);

        pendulum->addToTheta1(dTheta);
        pendulum->setOmega1(0); // Reset angular velocities
        pendulum->setOmega2(0);
}

void PendulumWidget::moveBob2(){
    QLine l1(bob1, last);
    QLine l2(bob1, current);
    float dTheta = getAngle(l1, l2);

    pendulum->addToTheta2(dTheta);
    pendulum->setOmega1(0); // Reset angular velocities
    pendulum->setOmega2(0);
}
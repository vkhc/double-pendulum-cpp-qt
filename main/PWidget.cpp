#include "PWidget.h"


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

}

void PendulumWidget::drawPendulum(QPainter& qp) {
    double l1 = pendulum->getL1();
    double l2 = pendulum->getL2();
    double theta1 = pendulum->getTheta1();
    double theta2 = pendulum->getTheta2();

    // Set scalefactor so that total length of pendulum is scaled 
    // up to roughly half of the screen
    float scaleFactor = (float)std::min(WIDTH, HEIGHT) / (l1 + l2) * 0.4;

    // Location of pivot point
    int pivotX = WIDTH / 2;
    int pivotY = HEIGHT / 2;
    // Location of bob 1
    bob1X = pivotX + l1 * sin(theta1) * scaleFactor;
    bob1Y = pivotY + l1 * cos(theta1) * scaleFactor;
    // Location of bob 2
    bob2X = bob1X + l2 * sin(theta2) * scaleFactor;
    bob2Y = bob1Y + l2 * cos(theta2) * scaleFactor;
    // Set bob size according
    int bobRadius = (l1 + l2) / 20 * scaleFactor;
    // Set pendulum rod width

    QPen pen(Qt::gray, 5, Qt::SolidLine);
    qp.setPen(pen);

    qp.drawLine(pivotX, pivotY, bob1X, bob1Y); // Pendulum 1
    qp.drawLine(bob1X, bob1Y, bob2X, bob2Y); // Pendulum 2
    pen.setColor(Qt::red);
    pen.setWidth(1);
    qp.setPen(pen);
    
    // Draw bob 1
    QRadialGradient gradientBob1(bob1X, bob1Y, bobRadius);
    gradientBob1.setColorAt(0.0, Qt::white);
    gradientBob1.setColorAt(1.0, Qt::red);
    qp.setBrush(gradientBob1);
    qp.drawEllipse(QPoint(bob1X, bob1Y), bobRadius, bobRadius);

    // Draw bob 2
    QRadialGradient gradientBob2(bob2X, bob2Y, bobRadius);
    gradientBob2.setColorAt(0.0, Qt::white);
    gradientBob2.setColorAt(1.0, Qt::red);
    qp.setBrush(gradientBob2);
    qp.drawEllipse(QPoint(bob2X, bob2Y), bobRadius, bobRadius);
}

void PendulumWidget::tracePendulum() {
    trace.emplace(trace.begin(), QPoint(bob2X, bob2Y));
    if (trace.size() >= traceLength) trace.pop_back();

    
}

void PendulumWidget::drawTrace(QPainter& qp, deque<QPoint> D, QColor color) { // Add color as a parameter
    int tail = traceLength;
    qp.setRenderHint(QPainter::SmoothPixmapTransform, true);
    QPen pen(color, 3);
    qp.setPen(pen);
    QLine line;
    
    int red = color.red();      // Get rgb values of input color
    int green = color.green();  // to use them for fading tail
    int blue = color.blue();    // in the loop below

    int n = 2;
    for (int i=n+6; i<D.size(); i+=n) { // By setting i to more than 0, trace will be behind the ball
        // qp.drawPoint(D[i]);
        line.setP1(D[i]);
        line.setP2(D[i-n]);
        // Add fading tail
        if (i > traceLength - tail) {
            // Function to give 1 at beginning of tail and 0 at the end of the line
            float y = -1.0f / traceLength * (i - (traceLength - tail)) + 1; 

            color.setRed(y * red);
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
    drawTrace(qp ,trace, Qt::green);
    drawPendulum(qp);  
    
}

void PendulumWidget::timerEvent(QTimerEvent* e) {
    Q_UNUSED(e);
    tracePendulum();

    // Divide timerEvent interval by reductionFactor to get small enough
    // Time steps for euler method
    int reductionFactor = 50;
    float t = (float)tStep/reductionFactor;
    // Do numerical approximation reductionFactor times
    for (int i=0; i<reductionFactor; ++i) { //
        pendulum->stepAdvanceEuler(t);
    }
    repaint(); // Call PaintEvent
}
#include "PWidget.h"


#include <QPainter>
#include <QTime>
#include <cmath>




PendulumWidget::PendulumWidget(QWidget* parent) : QWidget(parent),
                                                  pendulum(new SinglePendulum) {
    // TODO: Orginize stylesheets properly
    setStyleSheet("background-color: black;");
    // TODO: Dynamic screen size?
    setFixedSize(800, 600);

    timerId = startTimer(tStep, Qt::PreciseTimer);

 
}


void PendulumWidget::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);
    
    // TODO: new QPainter on every repaint?
    QPainter qp(this);
    pendulum->drawPendulum(qp);
    
}

void PendulumWidget::timerEvent(QTimerEvent* e) {
    Q_UNUSED(e);

    pendulum->stepAdvance(tStep);

    repaint(); // Call PaintEvent
}
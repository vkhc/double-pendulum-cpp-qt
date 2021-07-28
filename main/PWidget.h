#pragma once

#include "pendulum.h"

#include <QWidget>
#include <memory>
#include <deque>
#include <utility>


using std::unique_ptr;
using std::deque;
using std::pair;


class PendulumWidget : public QWidget {
public:
    PendulumWidget(QWidget* parent = nullptr);

    void drawPendulum(QPainter& qp);
    void drawTrace(QPainter& qp);
    void tracePendulum();

protected:
    void paintEvent(QPaintEvent* e) override;
    void timerEvent(QTimerEvent* e) override;


private:
    unique_ptr<DoublePendulum> pendulum;
    int tStep = 15; // Time step [ms]
    int timerId;

    
    const int WIDTH = 800;
    const int HEIGHT = 600;

    int bob1X;
    int bob1Y;
    int bob2X;
    int bob2Y;

    deque<QPoint> trace;
    int traceLength = 200;


    bool traceP = false;

};
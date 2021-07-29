#pragma once

#include "pendulum.h"

#include <QWidget>
#include <QMouseEvent>
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
    void drawTrace(QPainter& qp, deque<QPoint> D, QColor color);
    void tracePendulum();

protected:
    void paintEvent(QPaintEvent* e) override;
    void timerEvent(QTimerEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;


private:
    void moveBob1();
    void moveBob2();


    unique_ptr<DoublePendulum> pendulum;
    int tStep = 15; // Time step [ms]
    int timerId;

    
    const int WIDTH = 800;
    const int HEIGHT = 600;

    QPoint pivot;
    QPoint bob1;
    QPoint bob2;

    deque<QPoint> trace;
    int traceLength = 100;


    bool traceP = false;
    bool active = true;
    bool mousePressed = false;
    bool bob1Snaped = false;
    bool bob2Snaped = false;

    QPoint offset;
    QPoint last;
    QPoint current;
};
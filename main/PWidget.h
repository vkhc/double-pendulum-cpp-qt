#pragma once

#include "pendulum.h"

#include <QWidget>
#include <QMouseEvent>
#include <memory>
#include <deque>

using std::unique_ptr;
using std::deque;


class PendulumWidget : public QWidget {
public:
    PendulumWidget(DoublePendulum* pPendulum, QWidget* parent = nullptr);

    void init();
    void drawRod1(QPainter& qp, QPen& pen);
    void drawRod2(QPainter& qp, QPen& pen);
    void drawBob1(QPainter& qp, QPen& pen);
    void drawBob2(QPainter& qp, QPen& pen);
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

public:
    bool rod1Draw = true;
    bool rod2Draw = true;
    bool bob1Draw = true;
    bool bob2Draw = true;

private:
    DoublePendulum* pendulum;
    int tStep = 15; // Time step [ms]
    int timerId;

    const int WIDTH = 800;
    const int HEIGHT = 600;
    float scaleFactor;
    int bobRadius;

    QPoint pivot;
    QPoint bob1;
    QPoint bob2;
    QPoint offset;
    QPoint last;
    QPoint current;

    deque<QPoint> trace;
    int traceLength = 100;
    
    // State vatiables
    bool traceP = false;
    bool mousePressed = false;
    bool bob1Snaped = false;
    bool bob2Snaped = false;

};
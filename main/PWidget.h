#pragma once

#include "pendulum.h"

#include <QWidget>
#include <memory>

using std::unique_ptr;


class PendulumWidget : public QWidget {
public:
    PendulumWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* e) override;
    void timerEvent(QTimerEvent* e) override;


private:
    unique_ptr<SinglePendulum> pendulum;
    int tStep = 10; // Time step [ms]
    int timerId;

};
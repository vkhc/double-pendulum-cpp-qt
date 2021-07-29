#pragma once

#include <QLine>

float getAngle(QLine& l1, QLine& l2);
bool doSnap(QPoint& mouse, QPoint& target, int radius);

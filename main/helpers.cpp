#include "helpers.h"
#include <cmath>



float getAngle(QLine& l1, QLine& l2) { // Get angle between two lines
    int dx1 = l1.x2() - l1.x1();
    int dx2 = l2.x2() - l2.x1();
    int dy1 = l1.y2() - l1.y1();
    int dy2 = l2.y2() - l2.y1();

    int crossProduct = dx1 * dy2 - dy1 * dx2;
    float l1Length = powf(dx1*dx1 + dy1*dy1, 0.5);
    float l2Length = powf(dx2*dx2 + dy2*dy2, 0.5);

    return -asinf(crossProduct / (l1Length  * l2Length));
}

bool doSnap(QPoint& mouse, QPoint& target, int radius) {
    QPoint diff = target - mouse;
    if (abs(diff.x()) < radius && abs(diff.y()) < radius) return true;
    return false;
}
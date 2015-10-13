/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Robot.h"
#include "constants.h"

Robot::Robot() : Unit() {}

Robot::Robot(const Robot& c) : Unit(c) {}

Robot* Robot::clone() const {
    return new Robot(*this);
}

bool Robot::attacks(const Unit& u) const {
    return (abs(x - u.x) <= 1 &&
            abs(y - u.y) <= 1);
}

void Robot::moveTowards(const Unit& u) {
    if (x > u.x) x--;
    if (x < u.x) x++;
    if (y > u.y) y--;
    if (y < u.y) y++;
    checkBounds();
}

bool Robot::isJunk() const {
    return false; // Will be overriden in Junk
}

void Robot::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                             JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(ROBOT_COLOR));
}

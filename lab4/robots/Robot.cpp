/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Robot.h"
#include "constants.h"

Robot::Robot() : Unit() {}

Robot::Robot(const Robot& c) : Unit(c) {}

bool Robot::isJunk() const {
    return false; // Will be overriden in Junk
}

void Robot::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                             JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(ROBOT_COLOR));
}
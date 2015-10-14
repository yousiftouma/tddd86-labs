/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Hero.h"
#include "constants.h"

Hero::Hero() : Unit() {}

Hero* Hero::clone() const {
    return new Hero(*this);
}

void Hero::moveTowards(const Point& pt) {
    if (x > pt.x) x--;
    if (x < pt.x) x++;
    if (y > pt.y) y--;
    if (y < pt.y) y++;
    checkBounds();
}


void Hero::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addRect(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                          UNIT_WIDTH, UNIT_HEIGHT), Qt::NoPen, QBrush(HERO_COLOR));
}

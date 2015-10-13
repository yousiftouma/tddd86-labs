/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef HERO_H
#define HERO_H

#include "Unit.h"
#include <QGraphicsScene>

class Hero : public Unit {
public:
    Hero();
    
    /*
     * Polymorphic copy method
     */
    Hero* clone() const override;
    
    /*
     * Moves the hero towards the given point
     */
    void moveTowards(const Point& pt);

    /*
    * Draws this hero onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene *scene) const override;
};

#endif // HERO_H

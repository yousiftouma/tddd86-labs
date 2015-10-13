/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    /*
     * Default constructor
     */
    Junk();

    /*
     * Turns robot into junk
     */
    Junk(Robot c);

    /*
     * Polymorphic clone method
     */
    Junk* clone() const;

    /*
     * Always false, junk can't move and thus not attack
     */
    bool attacks(const Unit& u) const override;

    /*
     * Empty method, junk can't move
     */
    void moveTowards(const Unit& u) override;

    /*
     * Returns true
     * /
    bool isJunk() const override;

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const;
};

#endif // JUNK_H

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
    Junk();
    Junk(Robot c);

    Junk* clone() const;

    bool attacks(const Unit& u) const override;
    void moveTowards(const Unit& u) override;

    bool isJunk() const override;

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const;
};

#endif // JUNK_H

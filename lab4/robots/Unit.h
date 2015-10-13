/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef UNIT_H
#define UNIT_H

#include <QGraphicsScene>
#include "utilities.h"

/* Root class for all pieces on the board.
 * Subclasses are Robot, Hero and Junk.
 */
class Unit {
public:
    Unit();
    Unit(const Unit& u);
    
    virtual ~Unit();

    /*
     * Polymorph copy method
     */
    virtual Unit* clone() const;

    /*
    * Return Point representation of Unit
    */
    Point asPoint() const;

    /*
    * Am I in the same square as u?
    */
    bool at(const Unit& u) const;

    /*
    * Teleport. Does not check for collision
    */
    void teleport();

    /*
     * Draws unit in the GUI
    */
    virtual void draw(QGraphicsScene* scene) const = 0;

    /*
    * Euclidean distance to u
    */
    double distanceTo(const Unit& u) const;
private:
    
    // Allow Robot and Hero to acces coordinates
    friend class Robot;
    friend class Hero;
    
    int x;  // x position of this unit
    int y;  // y position of this unit

    // private helpers
    void checkBounds();
};

#endif // UNIT_H

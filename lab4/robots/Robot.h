/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
public:
    
    /*
     * Empty constructor
     */
    Robot();
    
    /*
     * Copy constructor
     */
    Robot(const Robot &c);

    /*
     * Polymorphic copying
     */
    Robot* clone() const override;
    
    /*
     * Can I catch u in one move?
     */
    virtual bool attacks(const Unit& u) const;
    
    /*
     * Take one step closer to u
     */
    virtual void moveTowards(const Unit& u);
    
    /*
     * Overloaded by Junk class, in Robot will allways return false
     */
    virtual bool isJunk() const;

    /*
     * Draws unit in the GUI
     */
    void draw(QGraphicsScene* scene) const override;
};

#endif // ROBOT_H

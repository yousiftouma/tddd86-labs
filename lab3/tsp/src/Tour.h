// Authors: vikho394, youto814
// Tour class implementing heuristics for TSP

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:

    /*
     * Empty Tour constructor
     */
    Tour();

    /*
     * Destructor, frees memory allocated for the internal linked list
     */
    ~Tour();

    /*
     * Prints all the nodes in order using the point toString method
     */
    void show();

    /*
     * Draws the Tour, i.e all point and their connecting edges to the scene
     */
    void draw(QGraphicsScene* scene);

    /*
     * Returns the number of nodes in the tour
     */
    int size();

    /*
     * Returns the total distance of the tour, i.e the sum of all edges between
     * points.
     */
    double distance();

    /*
     * Inserts the point at the optimal place according to the insert nearest
     * heuristic
     */
    void insertNearest(Point p);

    /*
     * Inserts the point at the optimal place in the tour according to the
     * insert smallest heuristic
     */
    void insertSmallest(Point p);

private:
    Node* front = nullptr;
};

#endif // TOUR_H

// Authors: vikho394, youto814
// Tour class implementing heuristics for TSP

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"
#include <limits>
#include <stack>

Tour::Tour() {}

Tour::~Tour()
{
    if (front == nullptr) {
        return;
    }
    Node* current = front->next;

    while (current != front) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    delete front;
}

void Tour::show()
{
    if (front == nullptr) {
        return;
    }
    Node* current = front;

    do {
        cout << current->point.toString() << endl;
        current = current->next;
    }
    while (current != front);
}

void Tour::draw(QGraphicsScene *scene)
{
    scene->clear();

    if (front == nullptr) {
        cout << "Empty tour" << endl;
        return;
    }

    Node* current = front;

    do {
        current->point.draw(scene);
        current->point.drawTo(current->next->point, scene);
        current = current->next;
    }
    while (current != front);
}

int Tour::size()
{
    int size = 0;

    if (front != nullptr) {
        Node* current = front;

        do {
            ++size;
            current = current->next;
        }
        while (current != front);
    }
    return size;
}

double Tour::distance()
{
    double dist = 0.0;

    if (front != nullptr) {
        Node* current = front;

        do {
            dist += current->point.distanceTo(current->next->point);
            current = current->next;
        }
        while (current != front);
    }
    return dist;
}

void Tour::insertNearest(Point p)
{
    double dist = numeric_limits<double>::infinity();
    Node* nearest = nullptr;

    if (front == nullptr) {
        Node* node = new Node(p, nullptr);
        node->next = node;
        front = node;
    }
    else {
        Node* current = front;
        do {
            double current_dist = p.distanceTo(current->point);
            if (current_dist < dist) {
                dist = current_dist;
                nearest = current;
            }
            current = current->next;
        }
        while (current != front);

        Node* new_node = new Node(p, nearest->next);
        nearest->next = new_node;
    }

}

double insertChange(Node* start, Point p) {
    double old_dist = start->point.distanceTo(start->next->point);
    double new_dist = p.distanceTo(start->point) +
            p.distanceTo(start->next->point);
    return new_dist - old_dist;
}

void Tour::insertSmallest(Point p)
{
    double best_diff = numeric_limits<double>::infinity();
    Node* best_node = nullptr;

    if (front == nullptr) {
        Node* node = new Node(p, nullptr);
        node->next = node;
        front = node;
    }
    else {
        Node* current = front;

        do {

            double old_dist = current->point.distanceTo(current->next->point);
            double new_dist = p.distanceTo(current->point) +
                    p.distanceTo(current->next->point);
            double current_dist = new_dist - old_dist;

            if (current_dist < best_diff) {
                best_diff = current_dist;
                best_node = current;
            }

            current = current->next;
        }
        while (current != front);

        Node* new_node = new Node(p, best_node->next);
        best_node->next = new_node;
    }
}

pair<Point*, Point*> getFarthestPoints(unordered_set<Point*> points) {
    pair<Point*, Point*> farthestPoints;
    double maxDist = -1;
    double currentDist;

    for (auto it1 = points.begin(); it1 != points.end(); ++it1) {
        for (auto it2 = it1; it2 != points.end(); ++it2){

            currentDist = (*it1)->distanceTo(*(*it2));
            if (currentDist >= maxDist){
                farthestPoints = make_pair(*it1, *it2);
                maxDist = currentDist;
            }
        }
    }
    return farthestPoints;
}


void Tour::insertFarthest(unordered_set<Point*> points) {

    // Too few points
    if (points.size() < 2) {
        return;
    }

    pair<Point*, Point*> farthestPoints = getFarthestPoints(points);

    // Remove points from set and insert them using insertsmallest
    insertSmallest(*farthestPoints.first);
    insertSmallest(*farthestPoints.second);
    points.erase(farthestPoints.first);
    points.erase(farthestPoints.second);
    delete farthestPoints.first;
    delete farthestPoints.second;

    while (!points.empty()) {

        double maxDist = -1;
        Point* pointToInsert;

        for (auto point : points) {
            double minDist = numeric_limits<double>::infinity();

            Node* current = front;

            do {
                double dist = point->distanceTo(current->point);

                if (dist < minDist) {
                    minDist = dist;
                }

                current = current->next;
            }
            while (current != front);

            // New farthest point found, update
            if (minDist > maxDist) {
                maxDist = minDist;
                pointToInsert = point;
            }

        }
        insertSmallest(*pointToInsert);
        points.erase(pointToInsert);
    }
}

void Tour::opt2Swap(Node* i, Node* k) {
    stack<Point> points;

    Node* current = i;
    do {
        points.push(current->point);
        current = current->next;

    } while(current != k->next);


    current = i;
    do {
        current->point = points.top();
        points.pop();
        current = current->next;

    } while(current != k->next);
}

double distanceIntervall(Node* start, Node* end) {
    double dist = 0;

    Node* current = start;
    do {
        dist += current->point.distanceTo(current->next->point);
        current = current->next;
    } while(current != end);
    return dist;
}

void Tour::opt2() {
    bool startOver = true;
    while (startOver) {
        startOver = false;

        //double bestDistance = distance();

        Node* outerCurrent = front->next;
        Node* outerPrev = front;

        do {
            Node* innerCurrent = outerCurrent->next;

            do {
                bool change = outerPrev->point.distanceTo(innerCurrent->point) +
                        outerCurrent->point.distanceTo(innerCurrent->next->point) <
                        outerPrev->point.distanceTo(outerCurrent->point) +
                        innerCurrent->point.distanceTo(innerCurrent->next->point);

                if (change) {
                    cout << "Did a swap!" << endl;
                    startOver = true;
                    opt2Swap(outerCurrent, innerCurrent); // Restore order
                }
                else {
                    startOver = false;
                }

                innerCurrent = innerCurrent->next;

            } while(!startOver && innerCurrent != front);


            outerCurrent = outerCurrent->next;
            outerPrev = outerPrev->next;
        } while(!startOver && outerCurrent->next != front);
    }
}






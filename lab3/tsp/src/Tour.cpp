// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"
#include <limits>

Tour::Tour()
{
    // TODO: write this member
}

Tour::Tour(Point a, Point b, Point c, Point d) {

    Node* node_a = new Node(a, nullptr);
    front = node_a;
    //node_a->next = front;

    Node* node_b = new Node(b, nullptr);
    node_a->next = node_b;

    Node* node_c = new Node(c, nullptr);
    node_b->next = node_c;

    Node* node_d = new Node(d, front);
    node_c->next = node_d;
}

Tour::~Tour()
{

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

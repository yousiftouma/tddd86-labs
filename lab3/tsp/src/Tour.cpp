// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

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
    // TODO: write this member
}

void Tour::show()
{
    if (front == nullptr) {
        cout << "Empty tour" << endl;
        return;
    }

    Node* current_slow = front;
    Node* current_fast = front;

    do {
        cout << current_slow->point.toString() << endl;
        current_slow = current_slow->next;
        current_fast = current_fast->next->next;
    }
    while (current_fast != current_slow);
}

void Tour::draw(QGraphicsScene *scene)
{
    // TODO: write this member
}

int Tour::size()
{
    int size = 0;

    if (front != nullptr) {
        Node* current_slow = front;
        Node* current_fast = front;

        do {
            ++size;
            current_slow = current_slow->next;
            current_fast = current_fast->next->next;
        }
        while (current_fast != current_slow);
    }
    return size;
}

double Tour::distance()
{
    double dist = 0.0;

    if (front != nullptr) {
        Node* current_slow = front;
        Node* current_fast = front;

        do {
            dist += current_slow->point.distanceTo(current_slow->next->point);
            current_slow = current_slow->next;
            current_fast = current_fast->next->next;
        }
        while (current_fast != current_slow);
    }
    return dist;
}

void Tour::insertNearest(Point p)
{
    // TODO: write this member
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}

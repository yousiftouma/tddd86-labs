// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

// Authors: Viktor Holmgren (vikho394), Yousif Touma (youto814)

#include "costs.h"
#include "trailblazer.h"
#include "queue.h"
#include "pqueue.h"
#include <limits>
#include <algorithm>
using namespace std;

/*
 * Traverses the graph using the depth first recursivly. Returns empty vector
 * if no path is found otherwise returns the path in reverse order (last to first).
 */
vector<Node* > dfsTraverse(BasicGraph& graph, Vertex* start, Vertex* end) {

    start->setColor(GREEN);

    // Base case, no possible path to end from here
    if (start->visited) {
        return vector<Node* >();

    }
    // End found return vector containing end
    else if (start == end) {
        vector<Node *> path;
        path.push_back(end);
        return path;
    }

    vector<Node *> path;
    start->visited = true;

    for (Arc* arc : start->arcs) {
        path = dfsTraverse(graph, arc->finish, end);

        // A successful path contains elements, return early if true
        if (!path.empty()) {
            path.push_back(start);
            return path;
        }
    }
    start->setColor(GRAY); // Dead end
    return path;
}

/*
 * Uses the dfsTraverse to traverse and then returns the correct path
 */
vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path = dfsTraverse(graph, start, end);
    reverse(path.begin(), path.end());
    return path;
}

/*
 * Builds a proper path by travsering from the end point using the previous pointers
 * all the way to the first node then reverses the order
 */
vector<Node* >buildProperPath(Vertex* end) {
    vector<Node* > path;
    Vertex* currentVertex = end;
    while (true) {
        if (currentVertex->previous == NULL) {
            path.push_back(currentVertex);
            break;
        }

        path.push_back(currentVertex);
        currentVertex = currentVertex->previous;
    }
    reverse(path.begin(), path.end());
    return path;
}

/*
 * Implementation of the BFS algorithm, using a queue
 */
vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Queue<Vertex*> nodeQueue;
    nodeQueue.enqueue(start);

    Vertex* currentVertex;
    while (!nodeQueue.isEmpty()) {
        currentVertex = nodeQueue.dequeue();
        currentVertex->setColor(GREEN);

        // End found
        if (currentVertex == end) {
            break;
        }
        currentVertex->visited = true;

        for (Vertex* neighbour : graph.getNeighbors(currentVertex)) {

            if (!neighbour->visited) {
                neighbour->visited = true;
                neighbour->previous = currentVertex;
                neighbour->setColor(YELLOW);
                nodeQueue.enqueue(neighbour);
            }
        }
    }
    return buildProperPath(end);
}

/*
 * Implementation of the Dijstras search algorithm using the stanford priority queue
 */
vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    PriorityQueue<Vertex*> pqueue;

    // Set initial costs
    for (Node* node : graph.getNodeSet()) {
        node->cost = numeric_limits<double>::infinity();
        pqueue.enqueue(node, node->cost);
    }

    // Enqueue the starting node
    start->cost = 0;
    pqueue.changePriority(start, 0);

    while (!pqueue.isEmpty()) {
        Vertex* currentBestVertex = pqueue.dequeue();
        currentBestVertex->setColor(GREEN);
        currentBestVertex->visited = true;

        // End found break early
        if (currentBestVertex == end) {
            break;
        }

        for (Vertex* neighbour : graph.getNeighbors(currentBestVertex)) {
            if (!neighbour->visited) {
                double cost = currentBestVertex->cost + graph.getArc(currentBestVertex, neighbour)->cost;
                if (cost < neighbour->cost) {
                    neighbour->cost = cost;
                    neighbour->previous = currentBestVertex;
                    neighbour->setColor(YELLOW);
                    pqueue.changePriority(neighbour, cost);
                }
            }
        }
    }
    return buildProperPath(end);
}

/*
 * Imlementation of the A* search algorithm using the stanford priority queue
 * and the given heuristic
 */
vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    PriorityQueue<Vertex*> pqueue;

    // Set initial costs
    for (Node* node : graph.getNodeSet()) {
        node->cost = numeric_limits<double>::infinity();
        pqueue.enqueue(node, node->cost);
    }

    // Enqueue the starting node
    start->cost = 0;
    pqueue.changePriority(start, start->heuristic(end));

    while (!pqueue.isEmpty()) {
        Vertex* currentBestVertex = pqueue.dequeue();
        currentBestVertex->setColor(GREEN);
        currentBestVertex->visited = true;

        // End found, break early
        if (currentBestVertex == end) {
            break;
        }

        for (Vertex* neighbour : graph.getNeighbors(currentBestVertex)) {
            if (!neighbour->visited) {
                double cost = currentBestVertex->cost + graph.getArc(currentBestVertex, neighbour)->cost;
                if (cost < neighbour->cost) {
                    neighbour->cost = cost;
                    neighbour->previous = currentBestVertex;
                    neighbour->setColor(YELLOW);
                    pqueue.changePriority(neighbour, cost + neighbour->heuristic(end));
                }
            }
        }
    }
    return buildProperPath(end);
}

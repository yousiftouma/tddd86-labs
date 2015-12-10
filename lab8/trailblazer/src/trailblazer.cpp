// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include "queue.h"
#include "pqueue.h"
#include <limits>
#include <algorithm>
// TODO: include any other headers you need; remove this comment
using namespace std;

vector<Node* > dfsTraverse(BasicGraph& graph, Vertex* start, Vertex* end) {

    start->setColor(GREEN);
    if (start->visited) {
        return vector<Node* >();

    }
    else if (start == end) {
        vector<Node *> path;
        path.push_back(end);
        return path;
    }

    vector<Node *> path;
    start->visited = true;

    for (Arc* arc : start->arcs) {

        path = dfsTraverse(graph, arc->finish, end);

        if (!path.empty()) {
            path.push_back(start);
            return path;
        }
    }
    start->setColor(GRAY);
    return path;
}


vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)

    graph.resetData();
    vector<Vertex*> path = dfsTraverse(graph, start, end);
    reverse(path.begin(), path.end());
    return path;
}


vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)

    graph.resetData();

    vector<Vertex*> path;
    Queue<Vertex*> nodeQueue;
    nodeQueue.enqueue(start);

    Vertex* currentVertex;
    while (!nodeQueue.isEmpty()) {
        currentVertex = nodeQueue.dequeue();
        currentVertex->setColor(GREEN);

        if (currentVertex == end) {
            break;
        }
        currentVertex->visited = true;

        for (Vertex* neighbour : graph.getNeighbors(currentVertex)) {

            if (!neighbour->visited) {
                neighbour->previous = currentVertex;
                neighbour->setColor(YELLOW);
                nodeQueue.enqueue(neighbour);
            }
        }
    }

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

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)

    graph.resetData();

    PriorityQueue<Vertex*> pqueue;

    // Set initial costs
    for (Node* node : graph.getNodeSet()) {
        node->cost = numeric_limits<double>::infinity();
        pqueue.enqueue(node, node->cost);
    }

    start->cost = 0;
    pqueue.changePriority(start, 0);

    Vertex* currentBestVertex;

    while (!pqueue.isEmpty()) {
        currentBestVertex = pqueue.dequeue();
        currentBestVertex->setColor(GREEN);
        currentBestVertex->visited = true;

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

    vector<Vertex*> path;
    while (true) {
        if (currentBestVertex->previous == NULL) {
            path.push_back(currentBestVertex);
            break;
        }

        path.push_back(currentBestVertex);
        currentBestVertex = currentBestVertex->previous;
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

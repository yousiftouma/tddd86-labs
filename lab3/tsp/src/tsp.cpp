/*
 * TDDD86 TSP
 * This client program uses your Tour class and contains the 'main'
 * function to open the input file and set up the program's primitive GUI.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <chrono>
#include <thread>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Point.h"
#include "Tour.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    string filename = "tsp1000.txt";
    //filename = "bier127.txt";
    ifstream input;
    input.open(filename);

    // get dimensions
    int width;
    int height;
    input >> width;
    input >> height;

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene();
    view->setScene(scene);
    view->scale(1, -1); //screen y-axis is inverted
    view->setSceneRect(0, 0, width, height);
    view->show();

    // run insertion heuristic
    Tour tour;
    unordered_set<Point*> points;
    double x;
    double y;
    Point* pp;

    std::clock_t start;
    start = std::clock();
    while (input >> x >> y) {
        //pp = new Point(x, y);
        //points.insert(pp);
        Point p{x,y};
        tour.insertNearest(p);
        //tour.insertSmallest(p);
        //uncomment the 4 lines below to animate
        //tour.draw(scene);
        //std::chrono::milliseconds dura(50);
        //std::this_thread::sleep_for(dura);
        a.processEvents();
    }
    //tour.insertFarthest(points);
    input.close();

    // print tour to standard output
    cout << "Tour distance: " << std::fixed << std::setprecision(4)
         << std::showpoint << tour.distance() << endl;
    //cout << "Number of points: " << tour.size() << endl;
    //tour.show();

    // draw tour
    tour.opt2();
    cout << "Tour distance: " << std::fixed << std::setprecision(4)
         << std::showpoint << tour.distance() << endl;
    tour.draw(scene);
    std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
    return a.exec(); // start Qt event loop
}

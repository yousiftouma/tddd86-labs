/*
 * TDDD86 Pattern Recognition
 * This program computes and plots all line segments involving 4 points
 * in a file using Qt.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"

// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}

Point COMPARATOR_POINT = Point(0, 0);
bool m_comparator(Point a, Point b) {
    //if (a.slopeTo(COMPARATOR_POINT) == b.slopeTo(COMPARATOR_POINT)) {
     //   return a < b;
    //}
    return a.slopeTo(COMPARATOR_POINT) < b.slopeTo(COMPARATOR_POINT);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // open file
    string filename = "input20.txt";
    ifstream input;
    input.open(filename);

    // the vector of points
    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Brute Force Pattern Recognition");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    for (auto f : points) {
        cout << f << endl;
    }
    cout << "--------------" << endl;

    auto begin = chrono::high_resolution_clock::now();


    int linesFound = 0;

    for (int i = 0; i < points.size() - 3; i++) {
        COMPARATOR_POINT = points[i];

        vector<Point>::const_iterator first = points.begin() + (i + 1);
        vector<Point>::const_iterator last = points.end();
        vector<Point> sorted(first, last);

        sort(sorted.begin(), sorted.end(), m_comparator);
        for (auto f : sorted) {
            cout << COMPARATOR_POINT << " " << f << " " << COMPARATOR_POINT.slopeTo(f) << endl;
        }
        cout << "--------------" << endl;

        int pointsOnSameSlope = 1;
        for (int j = 1; j < sorted.size(); j++) {
            bool comparison = sorted[j].slopeTo(COMPARATOR_POINT) == sorted[j-1].slopeTo(COMPARATOR_POINT);
            cout << "comparing j: " << sorted[j].slopeTo(COMPARATOR_POINT) << " and j-1: " << sorted[j-1].slopeTo(COMPARATOR_POINT) << endl;
            if (comparison) {
                cout << "incremented points on line to " << pointsOnSameSlope + 1 << endl;
                pointsOnSameSlope++;
            }
            if (!comparison) {
                if (pointsOnSameSlope >= 3) {
                    cout << "found a line with " << pointsOnSameSlope + 1 << " points!" << endl;
                    cout << "they have slope " << sorted[j-1].slopeTo(COMPARATOR_POINT) << endl;
                    cout << "and startpoint: " << points[i] << " and endpoint: " << sorted[j-1] << endl;
                    render_line(scene, points[i], sorted[j-1]);
                    a.processEvents();
                    linesFound++;
                }
                pointsOnSameSlope = 1;
            }
            else if (j == sorted.size()-1) {
                if (pointsOnSameSlope >= 3) {
                    cout << "found a line with " << pointsOnSameSlope + 1 << " points!" << endl;
                    cout << "they have slope " << sorted[j].slopeTo(COMPARATOR_POINT) << endl;
                    cout << "and startpoint: " << points[i] << " and endpoint: " << sorted[j-1] << endl;
                    render_line(scene, points[i], sorted[j]);
                    a.processEvents();
                    linesFound++;
                }
                pointsOnSameSlope = 1;
            }
        }
    }


    /*
    // iterate through all combinations of 4 points
    for (int i = 0 ; i < N-3 ; ++i) {
        for (int j = i+1 ; j < N-2 ; ++j) {
            for (int k = j+1 ; k < N-1 ; ++k) {
                //only consider fourth point if first three are collinear
                if (points.at(i).slopeTo(points.at(j)) == points.at(i).slopeTo(points.at(k))) {
                    for (int m{k+1} ; m < N ; ++m) {
                        if (points.at(i).slopeTo(points.at(j)) == points.at(i).slopeTo(points.at(m))) {
                            render_line(scene, points.at(i), points.at(m));
                            linesFound++;
                            a.processEvents(); // show rendered line
                        }
                    }
                }
            }
        }
    }
    */

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;
    cout << "Lines found: " << linesFound << endl;

    return a.exec(); // start Qt event loop
}

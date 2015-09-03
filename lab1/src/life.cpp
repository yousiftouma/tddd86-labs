// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include "unistd.h"
#include <string>
#include <fstream>

using namespace std;

Grid<char> grid = Grid<char>();

void showWelcomeMsg (){
    const char *msg =
            "Welcome to the TDDD86 Game of Life, \n"
            "a simulation of the lifecycle of a bacteria colony. \n"
            "Cells (X) live and die by the following rules: \n"
            "- A cell with 1 or fewer neighbours dies. \n"
            "- Locations with 2 neighbours remain stable. \n"
            "- Locations with 3 neighbours will create life. \n"
            "- A cell with 4 or more neighbours dies.";
    cout << msg << endl;
}

void openUserFile(ifstream& input) {
    while (true) {
        string fileName;
        cout << "Enter filename: ";
        getline(cin, fileName);

        input.open(fileName.c_str());
        if (input.is_open()) break;

        cout << "Sorry, I can't find a file with that name" << endl;
        input.clear();
    }

}

void printGrid() {
    for (int row = 0; row < grid.numRows(); ++row) {
        cout << endl;
        for (int col = 0; col < grid.numCols(); ++col)
            cout << grid.get(row, col);
    }
    cout << endl;
}

void loadGrid(ifstream& input){
    int rows, cols;
    input >> rows >> cols;

    // dummystring to absorb the new line
    string dummy;
    getline(input, dummy);

    grid.resize(rows, cols);

    for (int row = 0; row < rows; ++row) {
        string line;
        getline(input, line);
        for (int col = 0; col < cols; ++ col) {
            grid.set(row, col, line[col]);
        }
    }
    printGrid();
}

void initGame() {
    ifstream input;
    openUserFile(input);
    loadGrid(input);
    //cout << input.rdbuf();
}

int countNeighbors(int row, int col) {
    int res = 0;
    for (int y = -1; y <= 1; ++y) {
        for (int x = -1; x <= 1; ++x) {
            if ( x != 0 || y != 0) {
                if (grid.inBounds(y + row, x + col) && grid.get(y + row, x + col) == 'X') {
                    res++;
                }
            }
        }
    }
    return res;
}

void doTick() {

    Grid<char> newGrid = grid; // Make a temporary copy

    for (int row = 0; row < grid.numRows(); ++row) {

        for (int col = 0; col < grid.numCols(); ++col) {

            int neighbors = countNeighbors(row, col);

            if (neighbors == 3)
                newGrid.set(row, col, 'X');
            else if (neighbors == 2)
                newGrid.set(row, col, grid.get(row, col));
            else
                newGrid.set(row, col, '-');
        }
    }
    grid = newGrid;
}

void startAnimation() {
    while (true) {
        doTick();
        printGrid();
        pause(100);
    }
}

int main() {

    // TODO: Finish the program!

    grid = Grid<char>();
    showWelcomeMsg();
    initGame();

    while (true) {
        cout << "a)nimate, t(ick, q)uit? ";
        string cmd;
        cin >> cmd;
        cout << endl;
        if (cmd == "a") {
            startAnimation();
        }
        else if (cmd == "t") {
            doTick();
            printGrid();
        }
        else if (cmd == "q") {
            break;
        }

    }
    return 0;
}

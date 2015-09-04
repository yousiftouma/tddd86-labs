// Author: Viktor Holmgren, Yosif Touma
// A simple Conway's Game of Life implementation, able to load patterns stored in external text files.
// The user can show whether to advance the patterns step-by-step or using an automatic animation which triggers every 100ms

#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include "unistd.h"
#include <string>
#include <fstream>

using namespace std;

Grid<char> grid = Grid<char>();

// Shows the welcome message to the user
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

// Asks the user for a file containing a pattern and opens it, stores the content in the ifstream
void openUserFile(ifstream& input) {
    while (true) {
        string fileName;
        cout << "Grid input file name? ";
        getline(cin, fileName);

        input.open(fileName.c_str());
        if (input.is_open()) break;

        cout << "Sorry, I can't find a file with that name" << endl;
        input.clear();
    }

}

// Displays the global grid in the console
void printGrid() {
    for (int row = 0; row < grid.numRows(); ++row) {
        cout << endl;
        for (int col = 0; col < grid.numCols(); ++col)
            cout << grid.get(row, col);
    }
    cout << endl;
}

// Loads the grid with a given starting pattern
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
    printGrid(); // Print the starting pattern
}

// Initialize the game
void initGame() {
    ifstream input;
    openUserFile(input);
    loadGrid(input);
}

// Returns the number of neighbors to a given position (living cells in contact)
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

// Steps the simulation forward one step in time
void doTick() {

    Grid<char> newGrid = grid; // make a temporary copy

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
    grid = newGrid; // update the grid
    printGrid(); // redraw the grid
}

// Start continuous animation (tick every 100ms)
void startAnimation() {
    while (true) {
        doTick();
        pause(100);
    }
}

int main() {
    showWelcomeMsg();
    initGame();

    const string CMD_OPTIONS_STRING = "a)animate, t)ick, q)uit ";

    while (true) {

        cout << CMD_OPTIONS_STRING;

        char cmdKey;
        cin >> cmdKey;
        cout << endl;

        if (cmdKey == 'a') {
            startAnimation();
        }
        else if (cmdKey == 't') {
            doTick();
        }
        else if (cmdKey == 'q') {
            break;
        }

    }
    cout << "Have a nice Life!" << endl;
    return 0;
}

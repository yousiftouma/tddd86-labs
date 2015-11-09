// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <grid.h>
// TODO: include any other header files you need

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    // Basic constructor
    Boggle();

    // Force game board constructor
    Boggle(string board);

    // Returns a string representation of the current board
    string getBoardStr();

private:

    struct Cube {
        vector<char> characters;

        // Returns the upturned character
        char getUp() {
            return characters[0];
        }
    };

    Grid<Cube> gameBoard = Grid<Cube>(BOARD_SIZE, BOARD_SIZE);

};

#endif

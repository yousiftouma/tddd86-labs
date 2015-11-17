// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include <algorithm>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

Boggle::Boggle() {
    this->generateRandomBoard();
}

void Boggle::generateRandomBoard() {

    for (int i = 0; i < NUM_CUBES; i++) {
        Cube cube;

        for (int j = 0; j < CUBE_SIDES; j++) {
            cube.characters.push_back(CUBES[i][j]);
        }

        shuffle(cube.characters); // Shuffle characters
        gameBoard.set(i/4, i%4, cube);
    }

    // Shuffle board
    shuffle(gameBoard);
}

void Boggle::setBoard(string board) {

    board = toUpperCase(board);

    for (int i = 0; i < NUM_CUBES; i++) {
        Cube cube;

        cube.characters.push_back(board[i]);
        gameBoard.set(i/4, i%4, cube);
    }
}

bool Boggle::isValidWord(string word) {
    return word.size() >= 4 && !takenWords.contains(word) && lexicon.contains(word);
}

void Boggle::addWord(string word) {
    takenWords.add(word);
    playerScore += word.size() - 3; // 1 point per char over 3
}

int Boggle::numWordsGuessed() {
    return takenWords.size();
}

string Boggle::getPlayerWords() {
    return takenWords.toString();
}

int Boggle::getPlayerScore() {
    return playerScore;
}

string Boggle::getBoardStr() {
    string res = "";
    for (int i = 0; i < gameBoard.nRows; i++) {
        for (int j = 0; j < gameBoard.nCols; j++) {
            res += gameBoard.get(i,j).getUp();
        }
        res += "\n";
    }
    return res;
}

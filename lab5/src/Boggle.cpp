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
    this->resetBoard();
}

void Boggle::resetBoard() {

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

    // Reset scores
    playerScore = 0;
    computerScore = 0;

    playerWords.clear();
    computerWords.clear();
}

void Boggle::setBoard(string board) {

    board = toUpperCase(board);

    for (int i = 0; i < NUM_CUBES; i++) {
        Cube cube;

        cube.characters.push_back(board[i]);
        gameBoard.set(i/4, i%4, cube);
    }
}

bool Boggle::isValidPlayerWord(string word) {
    return word.size() >= 4 && !playerWords.contains(word) && lexicon.contains(word) &&
            this->existsOnBoard(word);
}

bool Boggle::existsOnBoard(string word) {

    bool res = false;
    for (int row = 0; row < gameBoard.nRows; row++) {
        for (int col = 0; col < gameBoard.nCols; col++) {
            res = res || recSearchWord(word, row, col);
        }
    }
    return res;
}

bool Boggle::recSearchWord(string word, int row, int col) {
    if (word.empty()) {
        return true;
    }
    else if (word[0] != gameBoard.get(row, col).getUp()) {
        return false;
    }
    bool res = false;
    Cube cube = gameBoard.get(row, col);
    cube.isMarked = true;
    gameBoard.set(row, col, cube);

    vector<int> neighbours = {-1, 0, 1};
    for (int dy : neighbours) {
        for (int dx : neighbours) {
            if ((dx != 0 || dy !=0) && gameBoard.inBounds(row + dy, col + dx)
                    && !gameBoard.get(row + dy, col + dx).isMarked) {

                res = res || recSearchWord(word.substr(1), row + dy, col + dx);
            }
        }
    }
    cube.isMarked = false;
    gameBoard.set(row, col, cube);
    return res;
}

void Boggle::addWord(string word) {
    playerWords.add(word);
    playerScore += word.size() - 3; // 1 point per char over 3
}

int Boggle::numPlayerWords() const {
    return playerWords.size();
}

string Boggle::getPlayerWords() {
    return playerWords.toString();
}

int Boggle::getPlayerScore() const {
    return playerScore;
}

int Boggle::numComputerWords() const {
    return computerWords.size();
}

int Boggle::getComputerScore() const {
    return computerScore;
}

string Boggle::getComputerWords() {
    return computerWords.toString();
}

bool Boggle::isValidComputerWord(string word) const {
    return word.size() >= 4 && lexicon.contains(word)
            && !computerWords.contains(word) && !playerWords.contains(word);
}

void Boggle::findAllWords() {
    for (int row = 0; row < gameBoard.nRows; row++) {
        for (int col = 0; col < gameBoard.nCols; col++) {
            this->recFindWords("", row, col);
        }
    }
}

void Boggle::recFindWords(string currentWord = "", int row = 0, int col = 0) {
    if (!lexicon.containsPrefix(currentWord)) return;

    if (isValidComputerWord(currentWord)) {
        computerWords.add(currentWord);
        computerScore += currentWord.size() - 3;
    }

    Cube cube = gameBoard.get(row, col);
    cube.isMarked = true;
    gameBoard.set(row, col, cube);

    vector<int> neighbours = {-1, 0, 1};
    for (int dy : neighbours) {
        for (int dx : neighbours) {
            if ((dx != 0 || dy !=0) && gameBoard.inBounds(row + dy, col + dx)
                    && !gameBoard.get(row + dy, col + dx).isMarked) {

                recFindWords(currentWord + cube.getUp(), row + dy, col + dx);
            }
        }
    }

    cube.isMarked = false;
    gameBoard.set(row, col, cube);
}

string Boggle::getBoardStr() const {
    string res = "";
    for (int i = 0; i < gameBoard.nRows; i++) {
        for (int j = 0; j < gameBoard.nCols; j++) {
            res += gameBoard.get(i,j).getUp();
        }
        res += "\n";
    }
    return res;
}

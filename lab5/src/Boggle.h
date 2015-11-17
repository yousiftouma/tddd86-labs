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
#include <set>
#include "lexicon.h"

// TODO: include any other header files you need

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    // Basic constructor
    Boggle();

    // Generates a random game board
    void resetBoard();

    // Force game board
    void setBoard(string board);

    // Adds the correct word to the player
    void addWord(string word);

    int numPlayerWords() const;

    int getPlayerScore() const;

    string getPlayerWords();

    // Returns whether the word is valid
    bool isValidPlayerWord(string word);

    bool existsOnBoard(string word);


    int numComputerWords() const;

    int getComputerScore() const;

    string getComputerWords();

    bool isValidComputerWord(string word) const;

    void findAllWords();

    // Returns a string representation of the current board
    string getBoardStr() const;

private:

    bool recSearchWord(string word, int row, int col);
    void recFindWords(string currentWord, int row, int col);

    const Lexicon lexicon = Lexicon(DICTIONARY_FILE);

    Set<string> playerWords;
    Set<string> computerWords;

    int playerScore = 0;
    int computerScore = 0;

    struct Cube {
        vector<char> characters;
        bool isMarked = false;

        // Returns the upturned character
        char getUp() const{
            return characters[0];
        }
    };

    Grid<Cube> gameBoard = Grid<Cube>(BOARD_SIZE, BOARD_SIZE);

};

#endif

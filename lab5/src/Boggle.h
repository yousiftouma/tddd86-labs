// Authors: Viktor Holmgren and Yousif Touma
// Contains all game logic for the boggle game.

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <grid.h>
#include <set>
#include "lexicon.h"

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    // Basic constructor
    Boggle();

    // Resets the state, generates a new random board
    void resetBoard();

    // Force a specific game board configuration
    void setBoard(string board);

    // Adds the correct word to the player
    void addWord(string word);

    // Returns the number of words correctly found by the player
    int numPlayerWords() const;

    // Returns the players current score
    int getPlayerScore() const;

    // Returns all the correct words found by the player (pretty format)
    string getPlayerWords();

    // Returns whether the word is valid
    bool isValidPlayerWord(string word);

    // Returns whether the word can be constructed with the given board
    bool existsOnBoard(string word);

    // Returns the number of word found by the computer
    int numComputerWords() const;

    // Returns the computers current score
    int getComputerScore() const;

    // Returns all words found by the computer (pretty format)
    string getComputerWords();

    // Checks if a given word follows the game rules and has not been found by the player
    bool isValidComputerWord(string word) const;

    // Algorithm for finding all possible word not found by the player, backtracking recursive
    void findAllWords();

    // Returns a string representation of the current board
    string getBoardStr() const;

private:

    // Recursive backtracking algorithm for finding if the word can be constructed from that position
    bool recSearchWord(string word, int row, int col);

    // Recursive backtracking algorithm for finding all possible words with the
    // prefix of currentWord from the given position
    void recFindWords(string currentWord, int row, int col);

    const Lexicon lexicon = Lexicon(DICTIONARY_FILE);

    Set<string> playerWords;
    Set<string> computerWords;

    int playerScore = 0;
    int computerScore = 0;

    struct Cube {
        vector<char> characters;
        bool isMarked = false; // Used for marking visited positions whilst backtracking

        // Returns the upturned character
        char getUp() const{
            return characters[0];
        }
    };

    Grid<Cube> gameBoard = Grid<Cube>(BOARD_SIZE, BOARD_SIZE);

};

#endif

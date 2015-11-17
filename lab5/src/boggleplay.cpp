// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
// TODO: include any other header files you need

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    // TODO: implement this function (and add any other functions you like to help you)

    boggle.resetBoard();
    if (!yesOrNo("Do you want to generate a random board (Y/N)?")) {
        string board = "";

        while (board.size() != 16) {
            cout << "Please enter a board string (16 characters)" << endl;
            getline(cin, board);
        }
        boggle.setBoard(board);
    }

    cout << "It's your turn!" << endl;

    cout << boggle.getBoardStr() << endl;

    // Player loop
    string line;
    cout << "Type a word (or press Enter to end your turn): " << endl;

    while(getline(cin, line)) {

        if (line.empty()) {
            break;
        }

        //TODO: clearConsole();
        line = toUpperCase(line);
        if (boggle.isValidPlayerWord(line)) {

            boggle.addWord(line);
            cout << "You found a new word! \"" << line << "\"" << endl;
        }

        cout << "Your words (" << boggle.numPlayerWords() << "): " << boggle.getPlayerWords() << endl;
        cout << "Your score: " << boggle.getPlayerScore() << endl;

        cout << boggle.getBoardStr() << endl;
        cout << "Type a word (or press Enter to end your turn): " << endl;
    }

    // Computer
    cout << "It's my turn!" << endl;
    boggle.findAllWords();
    cout << "My words (" << boggle.numComputerWords() << "): " << boggle.getComputerWords() << endl;
    cout << "My score: " << boggle.getComputerScore() << endl;

    // Game finish
    if (boggle.getPlayerScore() >= boggle.getComputerScore()) {
        cout << "Good job! You won" << endl;
    }
    else {
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
    }
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}

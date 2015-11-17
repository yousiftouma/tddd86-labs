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

    cout << "Do you want to generate a random board? (y/n)";
    string ans;
    cin >> ans;
    cin.ignore(); // Flush

    if (ans == "n") {
        string board = "";

        while (board.size() != 16) {
            cout << "Please enter a board string (16 characters)" << endl;
            getline(cin, board);
        }
        boggle.setBoard(board);
    }
    else {
        boggle.generateRandomBoard();
    }


    cout << "It's your turn!" << endl;

    cout << boggle.getBoardStr() << endl;

    // Player loop
    string line;
    cout << "Type a word (or press Enter to end your turn): " << endl;

    while(getline(cin, line)) {
        if (boggle.isValidWord(line)) {
            line = toUpperCase(line);
            boggle.addWord(line);
            cout << "You found a new word! \"" << line << "\"" << endl;
        }

        cout << "Your words (" << boggle.numWordsGuessed() << "): " << boggle.getPlayerWords() << endl;
        cout << "Your score: " << boggle.getPlayerScore() << endl;
        cout << "Type a word (or press Enter to end your turn): " << endl;
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

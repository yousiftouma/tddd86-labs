#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
using namespace std;

const string alphabet  = "abcdefghijklmnopqrstuvwxyz";

vector<string> loadDictionary(ifstream& input) {
    vector<string> wordList;
    while (!input.eof()) {
        string word;
        getline(input, word);
        wordList.push_back(word);
    }

    return wordList;
}

void printGuessedChars(set<char>& guessedChars) {
    cout << "Your guesses so far: ";
    for (auto iter = guessedChars.begin(); iter != guessedChars.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl;
}

char makeGuess(set<char>& guessedChars){
    char guess;
    while (true) {
        cout << "Please enter a guess: ";
        cin >> guess;
        if (guessedChars.find(guess) == guessedChars.end() && alphabet.find(guess) != string::npos){
            guessedChars.insert(guess);
            return guess;
        }
    }
}

void hangman(vector<string> wordList, bool logSize, int numberOfGuesses) {
    set<char> guessedChars = set<char>();
    for (int guessesLeft = numberOfGuesses; guessesLeft > 0; --guessesLeft) {
        cout << "Guesses left: " << guessesLeft << endl;
        printGuessedChars(guessedChars);
        makeGuess(guessedChars);
    }
}

int main() {
    cout << "Welcome to Hangman." << endl;

    ifstream dictionaryFile;
    dictionaryFile.open("di.txt");
    vector<string> wordList = loadDictionary(dictionaryFile);
    dictionaryFile.close();

    int wordLength;
    while (true) {
        cout << "Please enter a wordlength: ";
        cin >> wordLength;
        cout << endl;
        vector<string> tempWords;
        for (string word : wordList) {
            if (word.size() == wordLength) {
                tempWords.push_back((word));
            }
        }
        if (tempWords.size() > 0) {
            wordList = tempWords;
            break;
        }
    }

    int numberOfGuesses = 0;
    while (numberOfGuesses <= 0) {
        cout << "How many guesses would you like to have? ";
        cin >> numberOfGuesses;
        cout << endl;
    }

    bool logSize = false;
    string ans;
    while(true) {
        cout << "Would you like to see how many possible words are left? y/n: ";
        cin >> ans;
        if (ans == "y") {
            logSize = true;
            break;
        } else if (ans == "n") break;
    }

    hangman(wordList, logSize, numberOfGuesses);

    return 0;
}

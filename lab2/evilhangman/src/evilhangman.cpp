#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <map>

using namespace std;

// Author: Viktor Holmgren, Yousif Touma
// A program that plays Hangman with the user, where the user does the guessing
// The program in fact cheats in order to improve its chances. They way it does this is
// by not actually choosing a word at the start, but instead use a ever smaller amount of words
// as the user keeps guessing.


const string alphabet  = "abcdefghijklmnopqrstuvwxyz";
const string dictionaryFilename = "dictionary.txt";

// Loads the dictionary of all valid words into our initial worldlist
vector<string> loadDictionary() {

    // Open file
    ifstream input;
    input.open(dictionaryFilename);

    vector<string> wordList;
    while (!input.eof()) {
        string word;
        getline(input, word);
        wordList.push_back(word);
    }
    input.close();
    return wordList;
}

// Prints all the guesses made by the user so far
void printGuessedChars(set<char>& guessedChars) {
    cout << "Your guesses so far: ";
    for (auto iter = guessedChars.begin(); iter != guessedChars.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl;
}

// Asks the user for character, i.e a guess. Validates that the user enters only one character and it has not been used before
char makeGuess(set<char>& guessedChars){
    string guess;

    while (true) {
        cout << "Please enter a guess: ";
        getline(cin, guess);

        if (guess.size() > 1) {
            cout << "Only enter one character!" << endl;
        } else if (guessedChars.find(guess[0]) == guessedChars.end() && alphabet.find(guess[0]) != string::npos){
            guessedChars.insert(guess[0]);
            return guess[0];
        }
    }
}

// Calculates the most optimal word family from a map of families, and returns the key of the familiy
string chooseWordFamiliy(map<string, vector<string> > families, vector<string>& wordList) {
    size_t largest = 0;
    string key;
    for (auto it = families.begin(); it != families.end(); ++it) {
        if (it->second.size() > largest) {
            key = it->first;
            largest = it->second.size();
        }
    }
    auto iter = families.find(key);
    wordList = iter->second;
    return key;
}

// Returns all word families with the given word length and matching the current word
map<string, vector<string> > makeWordFamilies(vector<string> wordList, int wordLength, string currentWord, char guess) {
    map<string, vector<string> > families;

    for (string word : wordList) {
        string key = currentWord;
        for (int i = 0; i < wordLength; ++i) {
            if (word[i] == guess) {
                key[i] = guess;
            }
        }
        if (families.find(key) == families.end()) {
            vector<string> tempVector;
            tempVector.push_back(word);
            families.insert(pair<string, vector<string> >(key, tempVector));
        } else {
            families[key].push_back(word);
        }
    }
    return families;
}

// Displays the choosen word and whether the user has won
void displayResult(bool hasWon, string word) {
    if (hasWon) {
        cout << "Congratulations! You won!" << endl;
    } else {
        cout << "Sorry, better luck next time!" << endl;
    }
    cout << "The word was: " << word << endl;
}

// Main function, calls the sub functions, i.e asking for input, calculating word families
void hangman(vector<string>& wordList, int wordLength, bool doLogging, int numberOfGuesses) {
    set<char> guessedChars = set<char>();
    string currentWord = string(wordLength, '-');

    while(numberOfGuesses > 0){

        cout << "Guesses left: " << numberOfGuesses << endl;
        printGuessedChars(guessedChars);
        cout << "Current word: " << currentWord << endl;

        if (doLogging) {
            cout << "Number of possible words: " << wordList.size() << endl;
        }

        char guess = makeGuess(guessedChars);
        map<string, vector<string> > families = makeWordFamilies(wordList, wordLength, currentWord, guess);
        string newCurrentWord = chooseWordFamiliy(families, wordList);

        if (newCurrentWord == currentWord) {
            --numberOfGuesses;
        }
        currentWord = newCurrentWord;

        if (currentWord.find('-') == string::npos) {
            displayResult(true, currentWord);
            return; // End game early, won
        }

        // Padding for next round
        cout << endl << endl;
    }
    displayResult(false, wordList.front());
}

int main() {

    while (true) {
        cout << "Welcome to Hangman." << endl;
        vector<string> wordList = loadDictionary();

        size_t wordLength;
        while (true) {
            cout << "Please enter a wordlength: ";
            cin >> wordLength;

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
        }

        bool doLogging = false;
        string ans;
        while(true) {
            cout << "Would you like to see how many possible words are left? y/n: ";
            cin >> ans;
            cin.clear(); // flush the cin buffer

            if (ans == "y" or ans == "n") {
                doLogging = ans == "y";
                break;
            }
        }

        cout << endl; // Padding
        hangman(wordList,wordLength, doLogging, numberOfGuesses);
        cout << "Do you want to try again (y/n): ";
        cin >> ans;
        cout << endl;

        if (ans == "n") {
            break;
        }
    }
    return 0;
}

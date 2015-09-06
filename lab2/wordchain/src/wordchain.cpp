#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <vector>

using namespace std;

// Author: Viktor Holmgren, Yousif Touma
// A program that calculates and displays the shortest wordchain between two given words (user input).
// Every word in the chain can only differ by one letter from the preciding and following word, also all words needs to be vaild,
// i.e inlcuded in the dictionary.txt file.


const string alphabet  = "abcdefghijklmnopqrstuvwxyz";

// Loads the specified file contents (inputstream) into the given set
void loadDictionary(ifstream& input, set<string>& dictionary) {
    while (!input.eof()) {
        string word;
        getline(input, word);
        dictionary.insert(word);
    }
}

// Returns all valid neighbouring words (words differing by one character and in the provided dictionary) to a given word
vector<string> neighbouringWords(string word, set<string>& validWords) {
    vector<string> words = vector<string>();
    for (size_t i = 0; i < word.size(); ++i) {
        for (auto character : alphabet) {
            string tempWord = word;
            tempWord[i] = character;

            if (tempWord[i] != word[i] && validWords.find(tempWord) != validWords.end()) {
                words.push_back(tempWord);
            }
        }
    }
    return words;
}


// Returns a stack of words, i.e the wordchain, if no connection is found an empty stack is returned
stack<string> wordChain(string startWord, string goalWord, set<string>& validWords) {

    set<string> alreadyVisited = set<string>(); // used to prevent infinite cycles from occuring

    queue<stack<string> > wordChains = queue<stack<string> >();

    // Setup the starting stack
    stack<string> tempStack = stack<string>();
    tempStack.push(startWord);
    wordChains.push(tempStack);

    while (!wordChains.empty()) {

        stack<string> wordStack = wordChains.front();
        wordChains.pop(); // Remove first elem

        if (wordStack.top() == goalWord) {
            return wordStack;
        } else {
            vector<string> neighbours = neighbouringWords(wordStack.top(), validWords);
            for (string word : neighbours) {
                if (alreadyVisited.find(word) == alreadyVisited.end()) {
                    alreadyVisited.insert(word);
                    stack<string> tempWordStack = wordStack;
                    tempWordStack.push(word);
                    wordChains.push(tempWordStack);
                }
            }
        }

    }
    return stack<string>();
}

// Prints a stack of strings (a wordchain)
void printResult(stack<string> resultChain) {

    if (resultChain.size() == 0) {
        cout << "Did not find any word chain for those words" << endl;
        return;
    }

    while (!resultChain.empty()) {
        string word = resultChain.top();
        cout << word << " ";
        resultChain.pop();
    }
    cout << endl;
}

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    string startWord, goalWord;
    cout << "Please type two words: ";
    cin >> startWord >> goalWord;
    cout << "Chain from " << goalWord << " back to " << startWord << ":" << endl;


    set<string> validWords = set<string>();
    ifstream dictionaryFile;
    dictionaryFile.open("dictionary.txt");
    loadDictionary(dictionaryFile, validWords);
    dictionaryFile.close();

    printResult(wordChain(startWord, goalWord, validWords));
    cout << "Have a nice day!" << endl;

    return 0;
}

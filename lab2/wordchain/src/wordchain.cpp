#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <vector>

using namespace std;

const string alphabet  = "abcdefghijklmnopqrstuvwxyz";

void loadDictionary(ifstream& input, set<string>& dictionary) {
    while (!input.eof()) {
        string word;
        getline(input, word);
        dictionary.insert(word);
    }
}

// Returns all valid neighbouring words (words in the provided dictionary) to a given word
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


stack<string> wordChain(string startWord, string goalWord, set<string>& validWords) {

    set<string> alreadyVisited = set<string>();

    queue<stack<string> > wordChains = queue<stack<string> >();
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
    cout << "Chain from " << startWord << " back to " << goalWord << ":" << endl;


    set<string> validWords = set<string>();
    ifstream dictionaryFile;
    dictionaryFile.open("dictionary.txt");
    loadDictionary(dictionaryFile, validWords);
    dictionaryFile.close();

    printResult(wordChain(startWord, goalWord, validWords));

    cout << "Have a nice day!" << endl;

    return 0;
}

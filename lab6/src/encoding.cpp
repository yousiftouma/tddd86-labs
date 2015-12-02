// Authors: Viktor Holmgren, Yousif Touma

#include "encoding.h"
#include <queue>

map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;

    while(true) {
        int byte = input.get();

        // EOF found
        if (byte == -1) {
            freqTable[PSEUDO_EOF] = 1;
            break;
        }
        freqTable[byte]++;
    }
    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {

    priority_queue<HuffmanNode> queue;

    // Empty file, nothing to encode
    if (freqTable.size() == 1 && freqTable.find(PSEUDO_EOF) != freqTable.end()) {
        return nullptr;
    }

    // Init node queue with all chars and their frequencies
    for (auto node : freqTable) {
        queue.push(HuffmanNode(node.first, node.second));
    }

    // Combine nodes into a single prefix tree
    while (queue.size() > 1) {
        HuffmanNode first = queue.top();
        queue.pop();

        HuffmanNode second = queue.top();
        queue.pop();
        queue.push(HuffmanNode(NOT_A_CHAR, first.count + second.count,
                               new HuffmanNode(first), new HuffmanNode(second)));
    }

    HuffmanNode root = queue.top();
    return new HuffmanNode(root);
}

/*
 * Helper function, traverses the prefix tree, adding leafs in the encodingMap
 * with the prefixpath as key
 */
void encodingTraverse(const string prefix, const HuffmanNode* node, map<int, string> &encodingMap) {
    if (node == nullptr) {
        return;
    }
    else if (node->isLeaf()) {
        encodingMap.insert(make_pair(node->character, prefix));
    }
    encodingTraverse(prefix + "0", node->zero, encodingMap);
    encodingTraverse(prefix + "1", node->one, encodingMap);
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;
    encodingTraverse("", encodingTree, encodingMap);
    return encodingMap;
}

/*
 * Helper function, writes a given string of ones and zeros as bits
 */
void writeStringAsBits(string str, obitstream& output) {
    for (size_t i = 0; i < str.size(); ++i) {
        output.writeBit(str[i] == '1' ? 1 : 0);
    }
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    while (true) {
        int byte = input.get();

        // Found EOF
        if (byte == -1) {
            writeStringAsBits(encodingMap.at(PSEUDO_EOF), output);
            break;
        }
        else {
            writeStringAsBits(encodingMap.at(byte), output);
        }
    }
}


void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    HuffmanNode* root = encodingTree;
    HuffmanNode* current = encodingTree;

    while (true) {
        char bit = input.readBit();

        if (bit == 0) {
            current = current->zero;
        }
        else {
            current = current->one;
        }

        if (current->isLeaf()) {
            if (current->character == PSEUDO_EOF) break;
            output.put(current->character);
            current = root;
        }
    }
}

/*
 * Writes the frequency table to the output on the following format "key1:value1 key2:value2 }"
 */
void writeFrequencyTable(map<int, int> freqTable, obitstream& output) {
    for (auto itr : freqTable) {
        output << itr.first << ':' << itr.second << ' ';
    }
    output << '}';
}

void compress(istream& input, obitstream& output) {
    map<int, int> freqTable = buildFrequencyTable(input);
    writeFrequencyTable(freqTable, output);

    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    map<int, string> encodingMap = buildEncodingMap(encodingTree);

    input.clear(); // removes any current eof/failure flags
    input.seekg(0, ios::beg); // rewind to begining
    encodeData(input, encodingMap, output);

    freeTree(encodingTree);
}

/*
 * Helper function, returns the frequency table by reading from a given input
 */
map<int, int> readFrequencyTable(ibitstream& input) {
    map<int, int> freqTable;
    string first, second;

    while (true) {
        // Read key
        while (true) {
            char temp = input.get();
            if (temp == ':') break;

            // End of header found
            if (temp == '}') return freqTable;
            first.push_back(temp);
        }

        // Read value
        while (true) {
            char temp = input.get();
            if (temp == ' ') break;
            second.push_back(temp);
        }

        // Insert key-value pair
        freqTable[stoi(first)] = stoi(second);
        first.clear();
        second.clear();
    }
}

void decompress(ibitstream& input, ostream& output) {
    map<int, int> freqTable = readFrequencyTable(input);
    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    decodeData(input, encodingTree, output);

    freeTree(encodingTree);
}
/*
 * Postorder traverse, frees allocated memory
 */
void freeTree(HuffmanNode* node) {
    if (node == nullptr) return;

    freeTree(node->zero);
    freeTree(node->one);
    delete[] node;
}

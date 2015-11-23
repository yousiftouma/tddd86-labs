// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
// TODO: include any other headers you need

map<int, int> buildFrequencyTable(istream& input) {
    // TODO: implement this function
    map<int, int> freqTable;

    while(true) {
        char byte = input.get();

        // EOF found
        if (byte == -1) {
            freqTable[PSEUDO_EOF] = 1;
            break;
        }
        else if (freqTable.find(byte) == freqTable.end()) {
            freqTable[byte] = 1; // New character detected
        }
        else {
            freqTable[byte]++;
        }
    }
    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {

    priority_queue<HuffmanNode> queue;

    // Empty file, nothing to encode
    if (freqTable.size() == 1 && freqTable.find(PSEUDO_EOF) != freqTable.end()) {
        return nullptr;
    }

    // Init queue with all chars and their frequencies
    for (auto node : freqTable) {
        queue.push(HuffmanNode(node.first, node.second));
    }

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

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;
    encodingTraverse("", encodingTree, encodingMap);
    return encodingMap;
}

void encodingTraverse(const string prefix, const HuffmanNode* node, map<int, string> &encodingMap) {
    if (node->isLeaf()) {
        encodingMap.insert(make_pair(node->character, prefix));
    }
    else {
        if (node->zero != nullptr) {
            encodingTraverse(prefix + "0", node->zero, encodingMap);
        }
        if (node->one != nullptr) {
            encodingTraverse(prefix + "1", node->one, encodingMap);
        }
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

void writeStringAsBits(string str, obitstream& output) {
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '1') {
            output.writeBit(1);
        }
        else {
            output.writeBit(0);
        }
        //output.writeBit(str[i] == "1" ? 1 : 0);
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

            if (current->character == PSEUDO_EOF) {
                break;
            }

            output.put(current->character);
            current = root;
        }
    }
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}

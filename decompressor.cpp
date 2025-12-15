#include "Decompressor.h"
#include "HuffmanTree.h"
#include <fstream>
#include <unordered_map>
#include <string>
#include <iostream>

void Decompressor::decompress(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cout << "Cannot open compressed file\n";
        return;
    }

    std::unordered_map<unsigned char, int> freqMap;
    int mapSize;
    in.read((char*)&mapSize, sizeof(mapSize));

    for (int i = 0; i < mapSize; i++) {
        unsigned char ch;
        int freq;
        in.read((char*)&ch, 1);
        in.read((char*)&freq, sizeof(int));
        freqMap[ch] = freq;
    }

    int padding;
    in.read((char*)&padding, sizeof(padding));

    HuffmanTree tree;
    tree.buildTree(freqMap);

    std::string bitStream;
    unsigned char byte;
    while (in.read((char*)&byte, 1)) {
        for (int i = 7; i >= 0; i--)
            bitStream += ((byte >> i) & 1) ? '1' : '0';
    }

    bitStream.erase(bitStream.end() - padding, bitStream.end());

    std::ofstream out(outputFile, std::ios::binary);
    HuffmanNode* curr = tree.getRoot();

    for (char bit : bitStream) {
        curr = (bit == '0') ? curr->left : curr->right;
        if (!curr->left && !curr->right) {
            out.write((char*)&curr->data, 1);
            curr = tree.getRoot();
        }
    }

    in.close();
    out.close();
    std::cout << "Decompression completed\n";
}

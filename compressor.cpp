#include "Compressor.h"
#include "HuffmanTree.h"
#include <fstream>
#include <unordered_map>
#include <string>
#include <iostream>


void Compressor::compress(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cout << "Cannot open input file\n";
        return;
    }

    std::unordered_map<unsigned char, int> freqMap;
    unsigned char ch;
    while (in.read((char*)&ch, 1))
        freqMap[ch]++;

    HuffmanTree tree;
    tree.buildTree(freqMap);

    std::unordered_map<unsigned char, std::string> codes;
    tree.getCodes(codes);

    in.clear();
    in.seekg(0);

    std::ofstream out(outputFile, std::ios::binary);

    // Write frequency table
    int mapSize = freqMap.size();
    out.write((char*)&mapSize, sizeof(mapSize));
    for (auto& p : freqMap) {
        out.write((char*)&p.first, 1);
        out.write((char*)&p.second, sizeof(int));
    }

    // Encode file
    std::string bitStream;
    while (in.read((char*)&ch, 1))
        bitStream += codes[ch];

    int padding = (8 - bitStream.size() % 8) % 8;
    for (int i = 0; i < padding; i++)
        bitStream += '0';

    out.write((char*)&padding, sizeof(padding));

    for (size_t i = 0; i < bitStream.size(); i += 8) {
        unsigned char byte = 0;
        for (int j = 0; j < 8; j++) {
            byte <<= 1;
            if (bitStream[i + j] == '1')
                byte |= 1;
        }
        out.write((char*)&byte, 1);
    }

    in.close();
    out.close();
    std::cout << "Compression completed\n";
}

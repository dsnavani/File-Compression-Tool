#pragma once

class HuffmanNode {
public:
    unsigned char data;
    int freq;
    HuffmanNode *left, *right;

    HuffmanNode(unsigned char d, int f) {
        data = d;
        freq = f;
        left = right = nullptr;
    }
};

#pragma once
#include <unordered_map>
#include <string>
#include <queue>
#include <vector>
#include "HuffmanNode.h"

class HuffmanTree {
private:
    struct Compare {
        bool operator()(HuffmanNode* a, HuffmanNode* b) {
            return a->freq > b->freq;
        }
    };

    HuffmanNode* root;
    void generateCodes(HuffmanNode* node,
                       const std::string& code,
                       std::unordered_map<unsigned char, std::string>& codes);

public:
    HuffmanTree();
    void buildTree(const std::unordered_map<unsigned char, int>& freqMap);
    void getCodes(std::unordered_map<unsigned char, std::string>& codes);
    HuffmanNode* getRoot();
};

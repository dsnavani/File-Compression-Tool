#include "HuffmanTree.h"

HuffmanTree::HuffmanTree() : root(nullptr) {}

void HuffmanTree::buildTree(const std::unordered_map<unsigned char, int>& freqMap) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> pq;

    for (auto& pair : freqMap)
        pq.push(new HuffmanNode(pair.first, pair.second));

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        HuffmanNode* parent = new HuffmanNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }
    root = pq.top();
}

void HuffmanTree::generateCodes(HuffmanNode* node, const std::string& code,
                                std::unordered_map<unsigned char, std::string>& codes) {
    if (!node) return;

    if (!node->left && !node->right)
        codes[node->data] = code;

    generateCodes(node->left, code + "0", codes);
    generateCodes(node->right, code + "1", codes);
}

void HuffmanTree::getCodes(std::unordered_map<unsigned char, std::string>& codes) {
    generateCodes(root, "", codes);
}

HuffmanNode* HuffmanTree::getRoot() {
    return root;
}

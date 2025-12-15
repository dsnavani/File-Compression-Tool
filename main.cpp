#include <iostream>
#include "Compressor.h"
#include "Decompressor.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage:\n";
        std::cout << "  compress <input> <output>\n";
        std::cout << "  decompress <input> <output>\n";
        return 1;
    }

    std::string mode = argv[1];
    if (mode == "compress") {
        Compressor c;
        c.compress(argv[2], argv[3]);
    } else if (mode == "decompress") {
        Decompressor d;
        d.decompress(argv[2], argv[3]);
    } else {
        std::cout << "Invalid mode\n";
    }
    return 0;
}

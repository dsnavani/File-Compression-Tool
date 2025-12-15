# File-Compression-Tool

A lossless file compression and decompression utility implemented in **C++** using **Huffman Coding**.  
This project is designed to demonstrate strong C++ fundamentals, object-oriented design.

---

## Overview

The tool compresses any binary file by analyzing byte frequencies and generating optimal variable-length prefix codes (Huffman codes).  
The compressed file contains both the encoded data and the metadata required to reconstruct the original file during decompression.

---

## How Compression Works

1. Read the input file in binary mode.
2. Treat each byte (0–255) as a symbol and build a frequency table.
3. Construct a Huffman Tree using a min-heap (priority queue).
4. Generate Huffman codes for each byte.
5. Encode the input file into a compressed bit stream.
6. Store the frequency table and padding information in the output file.

---

## How Decompression Works

1. Read the frequency table from the compressed file.
2. Rebuild the Huffman Tree.
3. Decode the bit stream using the tree.
4. Write the original bytes back to the output file.

---

## Build Instructions

Compile all source files together:

```bash
HuffmanTree.cpp Compressor.cpp Decompressor.cpp main.cpp -o huffman
```
Usage
Compress a file
```bash
./huffman compress input_file output_file.huff
```
Decompress a file
```bash
./huffman decompress sample.huff restored.txt
```

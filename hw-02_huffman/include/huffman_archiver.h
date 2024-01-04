#ifndef HUFFMAN_ARCHIVER_H
#define HUFFMAN_ARCHIVER_H

#include "huffman_tree.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <exception>

namespace Huffman {
    class HuffmanArchiver {
    public:
        void archive(const std::string& input, const std::string& output);
        void read(const std::string& input);
        void write(const std::string& output) const;
    private:
        std::string _input;
        FrequencyTable _frequency_table;
        std::array<std::string, NUM_OF_BYTES> _codes;
    };

    class Encoder {
    public:
        explicit Encoder(std::array<std::string, NUM_OF_BYTES> codes);
        [[nodiscard]] std::string encode(const std::string &str) const;
    private:
        std::array<std::string, NUM_OF_BYTES> _codes;
    };
}

#endif
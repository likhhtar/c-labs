#ifndef HUFFMAN_UNARCHIVER_H
#define HUFFMAN_UNARCHIVER_H

#include "huffman_tree.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <exception>

namespace Huffman {

    class HuffmanUnarchiver {
    public:
        void unarchive(const std::string& input, const std::string& output);
        void read(const std::string& input);
        void write(const std::string& output) const;
    private:
        FrequencyTable _frequency_table;
        std::size_t _extra_bits;
        std::string _output;
        std::array<std::string, NUM_OF_BYTES> _codes;
    };
}

#endif
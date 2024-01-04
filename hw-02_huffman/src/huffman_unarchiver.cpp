#include "huffman_unarchiver.h"
#include <unordered_map>
#include <utility>

using namespace Huffman;


void HuffmanUnarchiver::unarchive(const std::string& input, const std::string& output) {
    try {
        read(input);
    } catch(const std::ifstream::failure& e) {
        std::cout << "Cannot read file!\n";
        return;
    }
    auto tree = new HuffmanTree(_frequency_table);
    _codes = tree->calc_codes();
    delete tree;
    try {
        write(output);
    } catch(const std::ifstream::failure& e) {
        std::cout << "Cannot write to file!\n";
        return;
    }
}

void HuffmanUnarchiver::read(const std::string& input) {
    std::ifstream in(input);
    in.exceptions(std::ifstream::failbit);

    for (std::size_t i = 0; i < NUM_OF_BYTES; i++) {
        in.read(reinterpret_cast<char *>(&_frequency_table._table[i]), sizeof(_frequency_table._table[i]));
    }
    in.read(reinterpret_cast<char *>(&_extra_bits), sizeof(_extra_bits));

    auto current_position = in.tellg();
    in.seekg(0, std::ios::end);
    _output.reserve(in.tellg() - current_position);
    in.seekg(current_position);
    _output.assign(std::istreambuf_iterator<char>(in),std::istreambuf_iterator<char>());
}

void HuffmanUnarchiver::write(const std::string& output) const {
    std::ofstream out(output);
    out.exceptions(std::ofstream::failbit);

    std::unordered_map<std::string, char> codes;
    for (std::size_t i = 0; i < _codes.size(); i++)
        codes[_codes[i]] = i;

    std::string current_code;
    std::size_t count = 0;
    for (std::size_t i = 0; i < _output.size(); i++) {
        for (int j = SIZE_OF_BYTE - 1; j >= 0; j--) {
            if ((std::size_t)j < _extra_bits && i == _output.size() - 1)
                break;
            current_code += ((((unsigned char)_output[i] >> j) & 1) ? "1" : "0");
            if (codes.find(current_code) != codes.end()) {
                char chr = codes[current_code];
                out.write(reinterpret_cast<const char *>(&chr), sizeof(chr));
                current_code.clear();
                count++;
            }
        }
    }
    std::cout << _output.length() << std::endl
              << count << std::endl
              << _frequency_table._table.size() * sizeof(_frequency_table._table[0]) + sizeof(_extra_bits) << std::endl;
}
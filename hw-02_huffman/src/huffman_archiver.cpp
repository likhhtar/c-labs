#include "huffman_archiver.h"

#include <utility>
#include "util.h"

using namespace Huffman;

void HuffmanArchiver::archive(const std::string& input, const std::string& output) {
    try {
        read(input);
    } catch(const std::ifstream::failure& e) {
        std::cout << "Cannot read file!" << std::endl;
        return;
    }
    _frequency_table.build_table(_input);
    auto tree = new HuffmanTree(_frequency_table);
    _codes = tree->calc_codes();
    delete tree;
    try {
        write(output);
    } catch(const std::ifstream::failure& e) {
        std::cout << "Cannot write to file!" << std::endl;
        return;
    }
}

void HuffmanArchiver::read(const std::string& input) {
    std::ifstream in(input);
    in.exceptions(std::ifstream::failbit);
    in.seekg(0, std::ios::end);
    _input.reserve(in.tellg());
    in.seekg(0, std::ios::beg);
    _input.assign(std::istreambuf_iterator<char>(in),std::istreambuf_iterator<char>());
}


void HuffmanArchiver::write(const std::string& output) const {
    std::ofstream out(output);
    out.exceptions(std::ofstream::failbit);
    for (auto e : _frequency_table._table) {
        out.write(reinterpret_cast<const char *>(&e), sizeof(e));
    }

    Encoder encoder(_codes);
    std::string encoded = encoder.encode(_input);
    std::size_t extra_bits = (SIZE_OF_BYTE - encoded.length() % SIZE_OF_BYTE) % SIZE_OF_BYTE;
    out.write(reinterpret_cast<const char *>(&extra_bits), sizeof(extra_bits));
    std::cout << _input.size() << std::endl
              << (encoded.size() + extra_bits) / SIZE_OF_BYTE << std::endl
              << _frequency_table._table.size() * sizeof(_frequency_table._table[0]) + sizeof(extra_bits) << std::endl;

    for (std::size_t i = 0; i < encoded.size(); i += SIZE_OF_BYTE) {
        unsigned char chr = convert_to_char(encoded.substr(i, std::min(encoded.size() - i,
                                                                                 (std::size_t)SIZE_OF_BYTE)));
        out.write(reinterpret_cast<const char *>(&chr), sizeof(chr));
    }
}

Encoder::Encoder(std::array<std::string, NUM_OF_BYTES> codes) : _codes(std::move(codes)) {};

std::string Encoder::encode(const std::string &str) const {
    std::string code;
    for (auto c : str)
        code += _codes[(unsigned char)c];
    return code;
}
#include "huffman_archiver.h"
#include "huffman_unarchiver.h"
#include <tuple>

using namespace Huffman;

std::tuple<std::string, std::string, std::string> parse(int argc, char** argv) {
    int num_args = 6;
    std::string act, input, output;
    if (argc < num_args)
        throw std::invalid_argument("Wrong arguments!\n");
    for (int i = 1; i < num_args; i++) {
        std::string arg(argv[i]);
        if (arg == "-c")
            act = "archive";
        else if (arg == "-u")
            act = "unarchive";
        else if ((arg == "-f" || arg == "--file") && i < num_args - 1) {
            input = argv[i + 1];
            i++;
        }
        else if ((arg == "-o" || arg == "--output") && i < num_args - 1) {
            output = argv[i + 1];
            i++;
        }
        else
            throw std::invalid_argument("Wrong arguments!\n");
    }
    if (act.empty() || input.empty() || output.empty())
        throw std::invalid_argument("Wrong arguments!\n");

    return std::make_tuple(act, input, output);
}

int main(int argc, char** argv) {
    try {
        auto args = parse(argc, argv);
        if (std::get<0>(args) == "archive") {
            HuffmanArchiver h;
            h.archive(std::get<1>(args), std::get<2>(args));
        }
        else {
            HuffmanUnarchiver h;
            h.unarchive(std::get<1>(args), std::get<2>(args));
        }
    } catch(const std::invalid_argument &e) {
        std::cout << e.what();
    }
    return 0;
}
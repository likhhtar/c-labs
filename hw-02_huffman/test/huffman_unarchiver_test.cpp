#include "doctest.h"
#include "huffman_unarchiver.h"
#include "util.h"

using namespace Huffman;

TEST_CASE("Unarchive tests") {
    HuffmanUnarchiver unarchiver;
    std::string output = "test/unarchive_test/output.txt";
    SUBCASE("Empty file") {
        unarchiver.unarchive("test/unarchive_test/empty_after.bin", output);
        CHECK(compare_files(output, "test/unarchive_test/empty.txt"));
    }
    SUBCASE("One letter file") {
        unarchiver.unarchive("test/unarchive_test/one_letter_after.bin", output);
        CHECK(compare_files(output, "test/unarchive_test/one_letter.txt"));
    }
    SUBCASE("Some txt file") {
        unarchiver.unarchive("test/unarchive_test/sometxt_after.bin", output);
        CHECK(compare_files(output, "test/unarchive_test/some_txt.txt"));
    }
}
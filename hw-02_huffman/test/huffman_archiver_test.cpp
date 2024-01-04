#include "doctest.h"
#include "huffman_archiver.h"
#include "util.h"

using namespace Huffman;


TEST_CASE("Encoder test") {
    std::array<std::string, NUM_OF_BYTES> codes;
    codes['a'] = "00";
    codes['b'] = "01";
    codes['c'] = "10";
    codes['d'] = "11";
    auto e = Encoder(codes);

    SUBCASE("Empty string") {
        CHECK_EQ(e.encode(""), "");
    }

    SUBCASE("String without repeats") {
        CHECK_EQ(e.encode("abcd"), "00011011");
    }

    SUBCASE("String with repeats") {
        CHECK_EQ(e.encode("ababcabcddcba"), "00010001100001101111100100");
    }
}

TEST_CASE("Archive test") {
    HuffmanArchiver archiver;
    std::string output = "test/archive_test/output.bin";
    SUBCASE("Empty file") {
        archiver.archive("test/archive_test/empty.txt", output);
        CHECK(compare_files(output, "test/archive_test/empty_after.bin"));
    }
    SUBCASE("One letter file") {
        archiver.archive("test/archive_test/one_letter.txt", output);
        CHECK(compare_files(output, "test/archive_test/one_letter_after.bin"));
    }
    SUBCASE("Some txt file") {
        archiver.archive("test/archive_test/sometxt.txt", output);
        CHECK(compare_files(output, "test/archive_test/sometxt_after.bin"));
    }
}
#include "doctest.h"
#include "huffman_tree.h"

using namespace Huffman;

TEST_CASE("HuffmanTreeNode test") {
    auto* node1 = new HuffmanTreeNode(nullptr, nullptr, 256, 'a');
    SUBCASE("Leaf") {
        CHECK_EQ(node1->get_left_child(), nullptr);
        CHECK_EQ(node1->get_symbol(), 'a');
        CHECK(node1->is_leaf());
    }

    auto* node2 = new HuffmanTreeNode(nullptr, nullptr, 17, 'b');
    HuffmanTreeNode node = HuffmanTreeNode(node1, node2, 273);
    SUBCASE("Not leaf") {
        CHECK_EQ(node.get_left_child(), node1);
        CHECK_EQ(node.get_right_child(), node2);
        CHECK_EQ(node.get_count(), 273);
        CHECK(!node.is_leaf());
    }

    SUBCASE("Not leaf's leaf") {
        CHECK_EQ(node.get_left_child()->get_right_child(), nullptr);
        CHECK_EQ(node.get_right_child()->get_symbol(), 'b');
        CHECK_EQ(node.get_left_child()->get_count() + node.get_right_child()->get_count(), 273);
    }

    HuffmanTreeNodeComparator cmp;
    SUBCASE("HuffmanTreeNodeComparator") {
        CHECK(!cmp(node1, node2));
        CHECK(cmp(node1, &node));
    }
}

TEST_CASE("FrequencyTable test") {
    SUBCASE("Empty string") {
        auto table = FrequencyTable("");
        for (auto a : table._table)
            CHECK_EQ(a, 0);
    }

    SUBCASE("One letter string") {
        auto table = FrequencyTable("aaaaaaaaaaaaa");
        for (std::size_t i = 0; i < table._table.size(); i++)
            if (i == 'a')
                CHECK_EQ(table._table[i], 13);
            else
                CHECK_EQ(table._table[i], 0);
    }

    SUBCASE("Random string 1") {
        auto table = FrequencyTable("abjAJaaAkJbbb...");
        CHECK_EQ(table._table['a'], 3);
        CHECK_EQ(table._table['b'], 4);
        CHECK_EQ(table._table['j'], 1);
        CHECK_EQ(table._table['A'], 2);
        CHECK_EQ(table._table['J'], 2);
        CHECK_EQ(table._table['k'], 1);
        CHECK_EQ(table._table['.'], 3);
    }

    SUBCASE("Random string 2") {
        auto table = FrequencyTable("she looks perfect");
        CHECK_EQ(table._table['s'], 2);
        CHECK_EQ(table._table['h'], 1);
        CHECK_EQ(table._table['e'], 3);
        CHECK_EQ(table._table['l'], 1);
        CHECK_EQ(table._table['o'], 2);
        CHECK_EQ(table._table['k'], 1);
        CHECK_EQ(table._table['p'], 1);
        CHECK_EQ(table._table['r'], 1);
        CHECK_EQ(table._table['f'], 1);
        CHECK_EQ(table._table['c'], 1);
        CHECK_EQ(table._table['t'], 1);
    }

    SUBCASE("Random string 3") {
        auto table = FrequencyTable("AMmama");
        CHECK_EQ(table._table['A'], 1);
        CHECK_EQ(table._table['M'], 1);
        CHECK_EQ(table._table['m'], 2);
        CHECK_EQ(table._table['a'], 2);
    }
}

TEST_CASE("HuffmanTree test") {
    std::array<std::string, NUM_OF_BYTES> codes;
    SUBCASE("Empty string") {
        auto tree = HuffmanTree(FrequencyTable(""));
        codes = tree.calc_codes();
        for (auto e : codes)
            CHECK_EQ(e, "");
    }

    SUBCASE("One letter string") {
        auto ht = HuffmanTree(FrequencyTable("aaaaaaaaaaaaa"));
        codes = ht.calc_codes();
        for (std::size_t i = 0; i < codes.size(); i++)
            if (i == 'a')
                CHECK_EQ(codes[i], "0");
            else
                CHECK_EQ(codes[i], "");
    }

    SUBCASE("Random string 1") {
        auto ht = HuffmanTree(FrequencyTable("abbabababcccccdddddd"));
        codes = ht.calc_codes();
        CHECK_EQ(codes['a'], "00");
        CHECK_EQ(codes['b'], "01");
        CHECK_EQ(codes['c'], "10");
        CHECK_EQ(codes['d'], "11");
    }

    SUBCASE("Random string 2") {
        auto ht = HuffmanTree(FrequencyTable("aaaaaaabbbbbccccdddeef"));
        codes = ht.calc_codes();
        CHECK_EQ(codes['a'], "11");
        CHECK_EQ(codes['b'], "01");
        CHECK_EQ(codes['c'], "00");
        CHECK_EQ(codes['d'], "100");
        CHECK_EQ(codes['e'], "1011");
        CHECK_EQ(codes['f'], "1010");
    }

    SUBCASE("Random string 3") {
        auto ht = HuffmanTree(FrequencyTable("AAAAABBBBB"));
        codes = ht.calc_codes();
        CHECK_EQ(codes['A'], "0");
        CHECK_EQ(codes['B'], "1");
    }

    SUBCASE("Random string 4") {
        auto ht = HuffmanTree(FrequencyTable("AAAAABBBBBCCCCC"));
        codes = ht.calc_codes();
        CHECK_EQ(codes['A'], "10");
        CHECK_EQ(codes['B'], "11");
        CHECK_EQ(codes['C'], "0");
    }

    SUBCASE("Random string 5") {
        auto ht = HuffmanTree(FrequencyTable("Hello"));
        codes = ht.calc_codes();
        CHECK_EQ(codes['H'], "00");
        CHECK_EQ(codes['e'], "01");
        CHECK_EQ(codes['l'], "11");
        CHECK_EQ(codes['o'], "10");
    }
}
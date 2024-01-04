#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <string>
#include <algorithm>
#include <set>

namespace Huffman {

    const std::size_t NUM_OF_BYTES = 256;
    const std::size_t SIZE_OF_BYTE = 8;

    class HuffmanTreeNode {
    public:
        HuffmanTreeNode(HuffmanTreeNode *lc, HuffmanTreeNode *rc, int count);
        HuffmanTreeNode(HuffmanTreeNode *lc, HuffmanTreeNode *rc, int count, char c);
        ~HuffmanTreeNode();
        [[nodiscard]] HuffmanTreeNode* get_left_child() const;
        [[nodiscard]] HuffmanTreeNode* get_right_child() const;
        [[nodiscard]] int get_count() const;
        [[nodiscard]] char get_symbol() const;
        [[nodiscard]] bool is_leaf() const;
    private:
        HuffmanTreeNode *_left_child;
        HuffmanTreeNode *_right_child;
        int _count;
        char _c{};
    };

    struct HuffmanTreeNodeComparator {
        bool operator()(const HuffmanTreeNode *a, const HuffmanTreeNode *b) const;
    };


    class FrequencyTable {
    public:
        FrequencyTable() = default;
        explicit FrequencyTable(const std::string &str);
        void build_table(const std::string &input);
    public:
        std::array<std::size_t, NUM_OF_BYTES> _table{};
    };


    class HuffmanTree {
    public:
        explicit HuffmanTree(const FrequencyTable &ft);
        ~HuffmanTree();
        [[nodiscard]] std::array<std::string, NUM_OF_BYTES> calc_codes() const;
        void merge_nodes() noexcept;
        void dfs(HuffmanTreeNode *node, std::array<std::string, NUM_OF_BYTES> &codes, const std::string& current_code) const;
    private:
        std::multiset<HuffmanTreeNode *, HuffmanTreeNodeComparator> _nodes;
        HuffmanTreeNode *_root = nullptr;
    };
}

#endif
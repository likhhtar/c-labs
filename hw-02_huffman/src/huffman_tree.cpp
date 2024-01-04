#include "huffman_tree.h"
#include <iostream>

using namespace Huffman;

HuffmanTreeNode::HuffmanTreeNode(HuffmanTreeNode *left_child, HuffmanTreeNode *right_child, int count)
                                : _left_child(left_child), _right_child(right_child), _count(count) {}

HuffmanTreeNode::HuffmanTreeNode(HuffmanTreeNode *left_child, HuffmanTreeNode *right_child, int count, char c) : HuffmanTreeNode(left_child, right_child, count) {
    _c = c;
}

HuffmanTreeNode::~HuffmanTreeNode() {
    delete _left_child;
    delete _right_child;
}

HuffmanTreeNode* HuffmanTreeNode::get_left_child() const  {
    return _left_child;
}

HuffmanTreeNode* HuffmanTreeNode::get_right_child() const  {
    return _right_child;
}

int HuffmanTreeNode::get_count() const {
    return _count;
}

char HuffmanTreeNode::get_symbol() const {
    return _c;
}

bool HuffmanTreeNode::is_leaf() const {
    return _left_child == nullptr && _right_child == nullptr;
}

bool HuffmanTreeNodeComparator::operator()(const HuffmanTreeNode *a, const HuffmanTreeNode *b) const {
    return a->get_count() < b->get_count();
}

FrequencyTable::FrequencyTable(const std::string &input) {
    build_table(input);
}

void FrequencyTable::build_table(const std::string &input) {
    for (auto e : input)
        _table[(unsigned char)e]++;
}


HuffmanTree::HuffmanTree(const FrequencyTable &ft) {
    for (std::size_t i = 0; i < ft._table.size(); i++) {
        if (ft._table[i] > 0)
            _nodes.insert(new HuffmanTreeNode(nullptr, nullptr, ft._table[i], (char) i));
    }
    while (_nodes.size() > 1)
        merge_nodes();
    if (_nodes.size() == 1)
        _root = *_nodes.begin();
}

HuffmanTree::~HuffmanTree() {
    delete _root;
}

std::array<std::string, NUM_OF_BYTES> HuffmanTree::calc_codes() const {
    std::array<std::string, NUM_OF_BYTES> codes;
    if (_root != nullptr) {
        std::string start_code;
        if (_root->is_leaf())
            start_code = "0";
        dfs(_root, codes, start_code);
    }
    return codes;
}

void HuffmanTree::merge_nodes() noexcept {
    HuffmanTreeNode* min1 = *_nodes.begin();
    _nodes.erase(_nodes.begin());
    HuffmanTreeNode* min2 = *_nodes.begin();
    _nodes.erase(_nodes.begin());
    _nodes.insert(new HuffmanTreeNode(min1, min2, min1->get_count() + min2->get_count()));
}

void HuffmanTree::dfs(HuffmanTreeNode* node, std::array<std::string, NUM_OF_BYTES> &codes, const std::string& current_code) const {
    if (node->is_leaf()) {
        codes[(unsigned char)node->get_symbol()] = current_code;
    }
    else {
        if (node->get_left_child() != nullptr)
            dfs(node->get_left_child(), codes, current_code + "0");
        if (node->get_right_child() != nullptr)
            dfs(node->get_right_child(), codes, current_code + "1");

    }
}
#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <stdlib.h>

class TrieNode {
public:
    TrieNode(void) {
        zero = NULL;
        one = NULL;
        data.clear();
    }

    void Clear(void) {
        zero = NULL;
        one = NULL;
        data.clear();
    }

    void SetZero(TrieNode * node) {
        zero = node;
    }

    TrieNode * GetZero(void) {
        return zero;
    }

    void SetOne(TrieNode * node) {
        one = node;
    }

    TrieNode * GetOne(void) {
        return one;
    }

    void SetData(const std::string & data) {
        this->data = data;
    }

    std::string & GetData(void) {
        return data;
    }

    void SetSize(const uint32_t size) {
        this->size = size;
    }

    uint32_t GetSize(void) {
        return size;
    }

private:
    TrieNode * zero;
    TrieNode * one;
    std::string data;
    uint32_t size;
};

class Trie {
public:
    Trie(void) {
        root.Clear();
    }

    void Insert(const std::string &, const unsigned int, const unsigned int, const std::string &);
    std::string Get(std::string);

private:
    TrieNode root;
};

#endif//TRIE_H

#include <iostream>
using namespace std;

#include "Trie.hpp"
#include "Game.hpp"

#include <vector>

TrieNode::TrieNode() {
    for(int i = 0; i < 26; i++) {
        children[i] = nullptr;
    }
    isEndOfTitle = false;
    game = nullptr;
}

TrieNode::~TrieNode() {
    for(int i = 0; i < 26; i++) {
        delete children[i];
    }
}

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    delete root;
}

std::string Trie::toSearchKey(std::string text) {
    int k = text.length();
    for(int i = 0; i < k; i++) {
        if (text[i] == 32) {
            for(int j = i; j < text.length()-1; j++) {
                text[j] = text[j+1];
            }
            i--;
            k -= 1;
        }
        else if(text[i] > 64 && text[i] < 91) {
            text[i] = text[i] + 32;
        }
    }
    return text.substr(0, k);
}

std::string Trie::insert(Game* game) {
    
}
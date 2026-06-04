#ifndef TRIE_HPP
#define TRIE_HPP

#include <vector>
#include <string>
#include "Game.hpp"

class TrieNode {

public:
    TrieNode* children[36];
    bool isEndOfTitle;
    Game* game;

    TrieNode();
    ~TrieNode();
};

class Trie {

private:
    TrieNode* root;

public:

    Trie();
    ~Trie();

    bool insert(Game* game);
    bool contains(std::string title);

    std::vector<Game*> autocomplete(std::string prefix, int k);

    std::string toSearchKey(std::string text);
    void sortResults(std::vector<Game*>& games);
    int partition(std::vector<Game*>& games, int low, int high);
    void quicksort(std::vector<Game*>& games, int low, int high);
};

#endif
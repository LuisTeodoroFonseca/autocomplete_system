#ifndef TRIE_HPP
#define TRIE_HPP

#include <vector>
#include <string>
#include "Game.hpp"

const int ALPHABET_SIZE = 36; // 26 letras + 10 dígitos

class TrieNode {

public:
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfTitle;
    Game* game;

    TrieNode();
    ~TrieNode();
};

class Trie {

private:
    TrieNode* root;

    // Métodos auxiliares privados
    void collectAll(TrieNode* node, std::vector<Game*>& results);
    int partition(std::vector<Game*>& games, int low, int high);
    void quicksort(std::vector<Game*>& games, int low, int high);
    int charToIndex(char c);

public:

    Trie();
    ~Trie();

    bool insert(Game* game);
    bool contains(std::string title);

    std::vector<Game*> autocomplete(std::string prefix, int k);

    std::string toSearchKey(std::string text);
    void sortResults(std::vector<Game*>& games);
};

#endif

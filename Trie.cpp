#include <iostream>
using namespace std;

#include "Trie.hpp"
#include "Game.hpp"

#include <vector>

// ==================== TrieNode ====================

TrieNode::TrieNode() {
    // Primeiras 26 posições: letras a-z
    // Últimas 10 posições: dígitos 0-9
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        children[i] = nullptr;
    }
    isEndOfTitle = false;
    game = nullptr;
}

TrieNode::~TrieNode() {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        delete children[i];
    }
}

// ==================== Trie ====================

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    delete root;
}

// Converte um caractere para o índice no array children.
// Letras minúsculas: índices 0-25
// Dígitos: índices 26-35
// Retorna -1 para caracteres inválidos.
int Trie::charToIndex(char c) {
    if (c >= 'a' && c <= 'z')
        return c - 'a';
    if (c >= '0' && c <= '9')
        return 26 + (c - '0');
    return -1;
}

// Converte título/prefixo para chave de busca:
// - converte para minúsculas
// - remove espaços
std::string Trie::toSearchKey(std::string text) {
    std::string result;
    for (char c : text) {
        if (c == ' ')
            continue;                     // ignora espaços
        if (c >= 'A' && c <= 'Z')
            c = c + 32;                   // converte para minúscula
        result += c;
    }
    return result;
}

// Insere um jogo na Trie usando o título como chave.
bool Trie::insert(Game* game) {
    if (game == nullptr)
        return false;

    TrieNode* current = root;
    std::string key = toSearchKey(game->getTitle());

    for (char c : key) {
        int index = charToIndex(c);
        if (index == -1)
            continue;
        if (current->children[index] == nullptr)
            current->children[index] = new TrieNode();
        current = current->children[index];
    }

    current->isEndOfTitle = true;
    current->game = game;
    return true;
}

// Verifica se existe um jogo com o título informado (case-insensitive, ignora espaços).
bool Trie::contains(std::string title) {
    if (title.empty())
        return false;

    TrieNode* current = root;
    std::string key = toSearchKey(title);

    for (char c : key) {
        int index = charToIndex(c);
        if (index == -1)
            continue;
        if (current->children[index] == nullptr)
            return false;
        current = current->children[index];
    }

    return current->isEndOfTitle;
}

// Coleta recursivamente todos os jogos da subárvore a partir de `node`.
void Trie::collectAll(TrieNode* node, std::vector<Game*>& results) {
    if (node == nullptr)
        return;
    if (node->isEndOfTitle && node->game != nullptr)
        results.push_back(node->game);
    for (int i = 0; i < ALPHABET_SIZE; i++)
        collectAll(node->children[i], results);
}

// Retorna até k jogos cujo título começa com o prefixo informado,
// ordenados por popularidade decrescente (empate: ordem alfabética pela chave).
std::vector<Game*> Trie::autocomplete(std::string prefix, int k) {
    std::vector<Game*> results;

    if (k <= 0)
        return results;

    // Navega até o nó correspondente ao prefixo
    TrieNode* current = root;
    std::string key = toSearchKey(prefix);

    for (char c : key) {
        int index = charToIndex(c);
        if (index == -1)
            continue;
        if (current->children[index] == nullptr)
            return results; // prefixo não encontrado
        current = current->children[index];
    }

    // Coleta todos os jogos da subárvore desse nó
    collectAll(current, results);

    // Ordena e limita a k resultados
    sortResults(results);

    if ((int)results.size() > k)
        results.resize(k);

    return results;
}

// ==================== Ordenação (Quicksort) ====================

// Compara dois jogos conforme critério do autocomplete:
// 1. Maior popularidade primeiro
// 2. Em caso de empate, menor chave de busca primeiro (ordem alfabética)
// Retorna true se `a` deve vir antes de `b`.
static bool comeAntes(Game* a, Game* b, Trie& trie) {
    if (a->getPopularity() != b->getPopularity())
        return a->getPopularity() > b->getPopularity();
    return trie.toSearchKey(a->getTitle()) < trie.toSearchKey(b->getTitle());
}

int Trie::partition(std::vector<Game*>& games, int low, int high) {
    Game* pivot = games[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (comeAntes(games[j], pivot, *this)) {
            i++;
            Game* tmp = games[i];
            games[i] = games[j];
            games[j] = tmp;
        }
    }

    // Coloca o pivô na posição correta
    Game* tmp = games[i + 1];
    games[i + 1] = games[high];
    games[high] = tmp;

    return i + 1;
}

void Trie::quicksort(std::vector<Game*>& games, int low, int high) {
    if (low >= high)
        return;
    int p = partition(games, low, high);
    quicksort(games, low, p - 1);
    quicksort(games, p + 1, high);
}

void Trie::sortResults(std::vector<Game*>& games) {
    if (games.empty())
        return;
    quicksort(games, 0, (int)games.size() - 1);
}

#include <iostream>
#include <string>
using namespace std;

#include "Trie.hpp"
#include "Game.hpp"
#include "GamesDatabase.hpp"

int main(int argc, char* argv[]) {
    // Verifica argumentos
    if (argc != 3) {
        cout << "Usage: ./app k prefix" << endl;
        return 1;
    }

    // Converte k para inteiro
    int k = 0;
    try {
        k = std::stoi(argv[1]);
    } 
    catch (...) {
        cout << "Usage: ./app k prefix" << endl;
        return 1;
    }

    std::string prefix = argv[2];

    // Cria a Trie
    Trie trie;

    // Insere todos os jogos
    for (int i = 0; i < numberOfGames; i++) {
        trie.insert(&games[i]);
    }

    // Executa autocomplete
    std::vector<Game*> results = trie.autocomplete(prefix, k);

    // Exibe resultados
    if (results.empty()) 
        cout << "No results found" << endl;
    else {
        for (Game* g : results) {
            cout << g->getTitle() << " | " << g->getShortDescription() << " | " << g->getPopularity() << endl;
        }
    }

    return 0;
}

#include <iostream>
#include <string>
using namespace std;

#include "Trie.hpp"
#include "Game.hpp"
#include "GamesDatabase.hpp"

int main(int argc, char* argv[]) {
    // 1. Verificar argumentos
    if (argc != 3) {
        cout << "Usage: ./app k prefix" << endl;
        return 1;
    }

    // 2. Converter k para inteiro
    int k = 0;
    try {
        k = std::stoi(argv[1]);
    } catch (...) {
        cout << "Usage: ./app k prefix" << endl;
        return 1;
    }

    std::string prefix = argv[2];

    // 3. Criar a Trie
    Trie trie;

    // 4. Inserir todos os jogos
    for (int i = 0; i < numberOfGames; i++) {
        trie.insert(&games[i]);
    }

    // 5. Executar autocomplete
    std::vector<Game*> results = trie.autocomplete(prefix, k);

    // 6. Exibir resultados
    if (results.empty()) {
        cout << "No results found" << endl;
    } else {
        for (Game* g : results) {
            cout << g->getTitle() << " | " << g->getShortDescription() << " | " << g->getPopularity() << endl;
        }
    }

    return 0;
}

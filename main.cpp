#include <iostream>
using namespace std;

#include "Trie.hpp"
#include "Game.hpp"
#include "GamesDatabase.hpp"

int main() {
    Trie trie = Trie();
    std::string texto1 = trie.toSearchKey("A b u 2");
    std::string texto2 = trie.toSearchKey("AB   U2");
    std::string texto3 = trie.toSearchKey("abu 2");
    cout << texto1 << endl;
    cout << texto2 << endl;
    cout << texto3 << endl;

    return 0;
}
#include <iostream>
using namespace std;

#include "Trie.hpp"
#include "Game.hpp"

#include <vector>

TrieNode::TrieNode() { //as primeiras 26 posições são para o alfabeto e as 10 últimas para os algarismos
    for(int i = 0; i < 36; i++) {
        children[i] = nullptr;
    }
    isEndOfTitle = false;
    game = nullptr;
}

TrieNode::~TrieNode() {
    for(int i = 0; i < 36; i++) {
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
        if (text[i] == 32) { //se o caractere for espaço, ele é excluido fazendo o array andar uma casa para a esquerda a partir da posição do espaço
            for(int j = i; j < text.length()-1; j++) {
                text[j] = text[j+1];
            }
            i--;
            k -= 1; //salva o tamanho do array formatado
        }
        else if(text[i] > 64 && text[i] < 91) { //se for maiscula transforma em minuscula
            text[i] = text[i] + 32;
        }
    }
    return text.substr(0, k);
}

bool Trie::insert(Game* game) {
    if(game == nullptr) 
        return false;

    TrieNode* current = root;
    std::string title = game->getTitle();
    title = toSearchKey(title);
    for(char c : title) {
        int index = -1;
        if(c >= 97 && c <= 122) //se for letra vai para as primeiras 26 posições do array children
            index = c - 97;       
        else if(c >= 48 && c <= 57) //se for número vai para as últimas 10 posições do array children
            index = c - 22;   
        if(index == -1)
            continue; 
        if(current->children[index] == nullptr) {
            current->children[index] = new TrieNode(); //cria novo nó se não existe alguma palavra que passa por aquele caminho
        }
        current = current->children[index];
    }
    current->isEndOfTitle = true;
    current->game = game;
    return true;
}

bool Trie::contains(std::string title) {
    if(title.empty()) 
        return false;

    std::string title_norm = toSearchKey(title);
    
    TrieNode* current = root;
    
    for(char c : title_norm) {
        int index = -1;
        if(c >= 97 && c <= 122)  //se for letra vai para as primeiras 26 posições do array children
            index = c - 97;       
        else if(c >= 48 && c <= 57) //se for número vai para as últimas 10 posições do array children
            index = c - 22;   
        if(index == -1)
            continue; 
        if(current->children[index] == nullptr) { //se não existir o caminho retorna false
            return false;
        }
        current = current->children[index];
    }
    if(current->isEndOfTitle == true)
        return true;
    else
        return false;
}
//escolhe um pivo e coloca todos os elementos com a maior popularidade (se for igual é por ordem alfabética) a esquerda dele e o resto coloca a direita dele.
int Trie::partition(std::vector<Game*>& games, int low, int high) {
    Game* pivo = games[low];

    int left = low + 1;
    int right = high;

    while (true) {
        while(left <= right && games[left]->getPopularity() >= pivo->getPopularity())
            if(games[left]->getPopularity() > pivo->getPopularity())
                left++;
            else if(games[left]->getPopularity() == pivo->getPopularity()) {
                if(games[left]->getTitle() < pivo->getTitle())
                    left++;
            }
            else
                break;
        while(left <= right && games[right]->getPopularity() <= pivo->getPopularity())
            if(games[right]->getPopularity() < pivo->getPopularity())
                right--;
            else if(games[right]->getPopularity() == pivo->getPopularity()) {
                if(games[right]->getTitle() > pivo->getTitle())
                    right--;
            }
            else
                break;;
        while(left > right)
            break;
        Game* aux1 = games[left];
        games[left] = games[right];
        games[right] = aux1;
    }
    Game* aux2 = games[low];
    games[low] = games[right];
    games[right] = aux2;

    return right;
}
//ordena a parte esquerda do pivo e depois a parte direita do pivo recursivamente
void Trie::quicksort(std::vector<Game*>& games, int low, int high){
    if(low >= high)
        return;

    int p = partition(games, low, high);
    
    quicksort(games, low, p-1);
    quicksort(games, p+1, high);
}

void Trie::sortResults(std::vector<Game*>& games) {
    if(games.empty())
        return;
    quicksort(games, 0, games.size()-1);
}
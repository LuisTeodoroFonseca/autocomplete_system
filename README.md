# Sistema de Autocomplete de Jogos com Trie

Sistema de autocomplete para um catálogo de jogos, implementado em C++ usando uma estrutura de dados **Trie**.

## Organização dos arquivos

```
main.cpp          — Ponto de entrada: lê argumentos, insere jogos e exibe resultados
Game.hpp / .cpp   — Classe que representa um jogo (título, descrição, popularidade)
Trie.hpp / .cpp   — Classes TrieNode e Trie com insert, contains, autocomplete e sortResults
GamesDatabase.hpp / .cpp — Lista estática de jogos usada nos testes
```

## Compilação

```bash
g++ main.cpp Game.cpp Trie.cpp GamesDatabase.cpp -o app
```

## Execução

```bash
./app k prefixo
```

- `k`: número máximo de sugestões a retornar
- `prefixo`: prefixo do título a buscar (case-insensitive, espaços ignorados)

Caso o prefixo contenha espaços, use aspas:

```bash
./app 3 "half l"
```

## Exemplos de uso

```bash
# Retorna até 3 jogos cujo título começa com "ha"
./app 3 ha

# Busca case-insensitive — equivalente ao anterior
./app 3 HA

# Espaços ignorados — equivalente a buscar "halfl"
./app 3 "half l"

# Sem resultados
./app 3 zelda

# k=0 retorna lista vazia
./app 0 ha
```

### Saída esperada para `./app 3 ha`

```
Hades | Defy the god of the dead... | 213542
Halo The Master Chief Collection | ... | 192219
Halo Infinite | ... | 160647
```

### Mensagens especiais

```
No results found   — nenhum jogo encontrado para o prefixo
Usage: ./app k prefix — argumentos incorretos
```

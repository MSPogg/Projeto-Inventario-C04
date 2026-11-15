#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <string>
#include <list>

enum Raridade {
    Comum,
    Raro,
    Epico,
    Lendario,
    Mitico
};

struct Item {
    std::string nome_item;
    std::string nome_dono;
    std::string propriedade_magica;
    int id;
    int valor_raridade;
    Raridade raridade;
};

struct Aresta {
    int destino;
    int similaridade;
};

struct Vertice {
    Item item;
    std::list<Aresta> adjacentes;
};

struct Grafo {
    std::list<Vertice> vertices;
};

// Árvore binária de busca
struct NoArvore {
    Item item;
    NoArvore *esquerda;
    NoArvore *direita;
};

Raridade classificarRaridade(int valor);
std::string nomeRaridade(Raridade raridade);
std::string corRaridade(Raridade raridade);
void exibirItem(const Item &item);
int lerInteiro(const std::string &mensagem);

// Funções do grafo
bool inserirVertice(Grafo &inventario, Item item);
bool existeItem(const Grafo &inventario, int id);
bool inserirSimilaridade(Grafo &inventario, int id1, int id2, int similaridade);
void exibirSimilaridadesBFS(const Grafo &inventario);
void buscarItensSimilares(const Grafo &inventario, int codigo, const std::string &jogador, int similaridade);
void removerVertice(Grafo &inventario, int id);

// Funções da árvore binária de busca
void inserirArvore(NoArvore* &p, Item novo_item);
bool existeItemPorNome(NoArvore* p, const std::string &nome);
void exibirEmOrdem(NoArvore* p);
int contarPropriedade(NoArvore* p, const std::string &propriedade);
bool removerArvore(NoArvore* &p, const std::string &nome, int id);
int removerMenosRaros(Grafo &inventario, NoArvore* &arvore, int r);
void destruirArvore(NoArvore* &p);

#endif

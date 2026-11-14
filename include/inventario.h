#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <string>
#include <list>

#include <map>


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

struct Aresta{
    int destino;
    int similaridade;
};

struct Vertice{
    Item item;
    std::list<Aresta> adjacentes;
};

struct Grafo{
    std::list<Vertice> vertices;
};

// Arvore binaria

struct treenode {
    Item item;
    struct treenode *left;
    struct treenode *right;
};

Raridade classificarRaridade(int valor);
void inserirItem(std::list<Item> &inventario_provisorio, Item novo_item);
bool inserirVertice(Grafo &inventario, Item item);
bool existeItem(const Grafo &inventario, int id);
bool inserirSimilaridade(Grafo &inventario, int id1, int id2, int similaridade);
void exibirSimilaridadesBFS(const Grafo &inventario);
void buscarItensSimilares(const Grafo &inventario, int codigo, const std::string &jogador, int similaridade);
bool existeItemPorNome(const std::list<Item> &inventario_provisorio, const std::string &nome);
int lerInteiro(const std::string &mensagem);
void tInsert(treenode* &p, Item novo_item);
std::string nomeRaridade(Raridade raridade);
std::string corRaridade(Raridade raridade);
void tShowInOrder(treenode* p);
int contarPropriedade(treenode* p, const std::string &propriedade);
bool tRemove(treenode* &p, const std::string &nome, int id);
void removerVertice(Grafo &inventario, int id);
int removerMenosRaros(Grafo &inventario, treenode* &arvore, int r);

#endif

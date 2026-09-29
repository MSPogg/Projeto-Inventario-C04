#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <string>
#include <list>

using namespace std;

enum Raridade {
    Comum,
    Raro,
    Epico,
    Lendario,
    Mitico
};

struct Item {
    string nome_item;
    string nome_dono;
    string propriedade_magica;
    int id;
    Raridade raridade;
};

struct Aresta{
    int destino;
    int similaridade;
};

struct Vertice{
    Item item;
    list<Aresta> adjacentes;
};

struct Grafo{
    list<Vertice> vertices;
};

Raridade classificarRaridade(int valor);
void inserirItem(list<Item> &inventario_provisorio, Item novo_item);
bool inserirVertice(Grafo &inventario, Item item);
bool existeItem(const Grafo &inventario, int id);
bool inserirSimilaridade(Grafo &inventario, int id1, int id2, int similaridade);
void exibirSimilaridadesBFS(const Grafo &inventario);
void buscarItensSimilares(const Grafo &inventario, int codigo, const string &jogador, int similaridade);

int lerInteiro(const string &mensagem);

#endif
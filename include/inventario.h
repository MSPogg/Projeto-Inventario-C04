#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <string>
#include <list>
#include <stack>

// Área máxima da abertura da Bolsa Devoradora
const float AREA_ABERTURA_BOLSA = 100.0;

struct Ponto {
    int x, y;
};

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
    float area_contorno;
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

// Funções de algoritmos geométricos
float area_triangulo(Ponto a, Ponto b, Ponto c);
int lado(Ponto a, Ponto b, Ponto p);
int orientacao(Ponto p1, Ponto p2, Ponto p3);
float distancia_quadrada(Ponto p1, Ponto p2);
Ponto anterior_top(std::stack<Ponto> &S);
int grahan_scan(Ponto pontos[], int n, Ponto poligono[]);
float calcular_area_poligono(Ponto poligono[], int m);
bool verificar_item_cabe_bolsa(Ponto pontos[], int n, float &area_calculada);

#endif
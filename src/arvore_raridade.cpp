
#include "arvore_raridade.h"
#include "menu.h"

#include <iostream>

using namespace std;

// Estrutura da arvore ja existente
struct NoRaridade {
    Item item;
    NoRaridade *esquerda;
    NoRaridade *direita;
};

// Insere os itens na ABB
void inserirRaridade(NoRaridade* &raiz, const Item &item) {

    if (raiz == nullptr) {
        raiz = new NoRaridade;
        raiz->item = item;
        raiz->esquerda = nullptr;
        raiz->direita = nullptr;
        return;
    }

    int novaRaridade = static_cast<int>(item.raridade);
    int raridadeAtual = static_cast<int>(raiz->item.raridade);

    if (novaRaridade < raridadeAtual ||
        (novaRaridade == raridadeAtual && item.id < raiz->item.id)) {

        inserirRaridade(raiz->esquerda, item);
    }
    else {
        inserirRaridade(raiz->direita, item);
    }
}

// Percurso decrescente: direita, raiz e esquerda
void imprimirDecrescente(NoRaridade *raiz) {

    if (raiz == nullptr) {
        return;
    }

    imprimirDecrescente(raiz->direita);

    cout << AMARELO << "┌─ " << RESET
         << NEGRITO << raiz->item.nome_item << RESET << endl;

    cout << "│ Dono: " << raiz->item.nome_dono << endl;

    cout << "│ Propriedade mágica: "
         << raiz->item.propriedade_magica << endl;

    cout << "│ ID: " << raiz->item.id << endl;

    cout << "│ Raridade: "
         << corRaridade(raiz->item.raridade)
         << nomeRaridade(raiz->item.raridade)
         << RESET << endl;

    cout << AMARELO
         << "└────────────────────────────────"
         << RESET << endl;

    imprimirDecrescente(raiz->esquerda);
}

// Libera a memoria utilizada pela arvore
void liberarArvore(NoRaridade *raiz) {

    if (raiz != nullptr) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        delete raiz;
    }
}

// Funcao principal da questao 8
void imprimirPorRaridade(const Grafo &inventario) {

    if (inventario.vertices.empty()) {
        cout << "Inventario vazio!" << endl;
        return;
    }

    NoRaridade *raiz = nullptr;

    // Insere todos os itens do grafo na nova ABB
    for (const Vertice &vertice : inventario.vertices) {
        inserirRaridade(raiz, vertice.item);
    }

    cout << NEGRITO
         << "\nITENS EM ORDEM DECRESCENTE DE RARIDADE\n\n"
         << RESET;

    imprimirDecrescente(raiz);

    liberarArvore(raiz);
}

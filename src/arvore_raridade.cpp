#include "arvore_raridade.h"
#include "menu.h"
#include <iostream>

using namespace std;

// Insere os itens na ABB ordenada pelo valor de raridade (0 a 100)
void inserirRaridade(NoArvore* &raiz, const Item &item) {
    if (raiz == nullptr) {
        raiz = new NoArvore;
        raiz->item = item;
        raiz->esquerda = nullptr;
        raiz->direita = nullptr;
        return;
    }

    if (item.valor_raridade < raiz->item.valor_raridade ||
        (item.valor_raridade == raiz->item.valor_raridade && item.id < raiz->item.id)) {
        inserirRaridade(raiz->esquerda, item);
    }
    else {
        inserirRaridade(raiz->direita, item);
    }
}

// Percurso decrescente: direita, raiz e esquerda
void exibirDecrescente(NoArvore *raiz) {
    if (raiz != nullptr) {
        exibirDecrescente(raiz->direita);
        exibirItem(raiz->item);
        exibirDecrescente(raiz->esquerda);
    }
}

// Função principal da opção 6 (listar em ordem decrescente de raridade)
void imprimirPorRaridade(const Grafo &inventario) {
    if (inventario.vertices.empty()) {
        cout << "Inventário vazio!" << endl;
        return;
    }

    NoArvore *raiz = nullptr;

    // Insere todos os itens do grafo na ABB de raridade
    for (const Vertice &vertice : inventario.vertices) {
        inserirRaridade(raiz, vertice.item);
    }

    cout << NEGRITO << "\nITENS EM ORDEM DECRESCENTE DE RARIDADE\n\n" << RESET;

    exibirDecrescente(raiz);

    destruirArvore(raiz);
}

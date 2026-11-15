// Arquivo para criar as funcionalidades do menu (funções do 1 ao 8)
#include "inventario.h"
#include "menu.h"
#include <string>
#include <iostream>
#include <list>

using namespace std;

Raridade classificarRaridade(int valor) {
    if (valor >= 100) {
        return Raridade::Mitico;
    }
    if (valor >= 85) {
        return Raridade::Lendario;
    }
    if (valor >= 60) {
        return Raridade::Epico;
    }
    if (valor >= 30) {
        return Raridade::Raro;
    }

    return Raridade::Comum;
}

string nomeRaridade(Raridade raridade) {
    switch (raridade) {
        case Comum: return "Comum";
        case Raro: return "Raro";
        case Epico: return "Épico";
        case Lendario: return "Lendário";
        case Mitico: return "Mítico";
    }
    return "";
}

string corRaridade(Raridade raridade) {
    switch (raridade) {
        case Comum: return VERDE;
        case Raro: return AZUL;
        case Epico: return ROXO;
        case Lendario: return AMARELO;
        case Mitico: return VERMELHO;
    }
    return RESET;
}

void exibirItem(const Item &item) {
    cout << AMARELO << "┌─ " << RESET << NEGRITO << item.nome_item << RESET << endl;
    cout << AMARELO << "│ " << RESET << "Dono: " << item.nome_dono << endl;
    cout << AMARELO << "│ " << RESET << "Propriedade mágica: " << item.propriedade_magica << endl;
    cout << AMARELO << "│ " << RESET << "ID: " << item.id << endl;
    cout << AMARELO << "│ " << RESET << "Raridade: " << item.valor_raridade << " (" << corRaridade(item.raridade) << nomeRaridade(item.raridade) << RESET << ")" << endl;
    cout << AMARELO << "└────────────────────────────────" << RESET << endl;
}

int lerInteiro(const string &mensagem) {
    int valor;

    while (true) {
        cout << mensagem;

        if (cin >> valor) {
            // Descarta o \n após leitura
            cin.ignore(10000, '\n');
            return valor;
        }

        cout << "Entrada inválida: digite um número inteiro." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

// Funções de Grafo (inserção de vértices e similaridade com lista de adjacência)

static bool contem(const list<int> &lista, int valor) {
    for (int elemento : lista) {
        if (elemento == valor) {
            return true;
        }
    }
    return false;
}

static Vertice *buscarVertice(Grafo &inventario, int id) {
    for (Vertice &vertice : inventario.vertices) {
        if (vertice.item.id == id) {
            return &vertice;
        }
    }
    return nullptr;
}

static const Vertice *buscarVertice(const Grafo &inventario, int id) {
    for (const Vertice &vertice : inventario.vertices) {
        if (vertice.item.id == id) {
            return &vertice;
        }
    }
    return nullptr;
}

bool existeItem(const Grafo &inventario, int id) {
    return buscarVertice(inventario, id) != nullptr;
}

// Insere o item como vértice do grafo, mantendo os vértices ordenados por id
bool inserirVertice(Grafo &inventario, Item item) {
    for (auto it = inventario.vertices.begin(); it != inventario.vertices.end(); it++) {
        if (it->item.id == item.id) {
            return false;
        }
        if (it->item.id > item.id) {
            inventario.vertices.insert(it, {item, {}});
            return true;
        }
    }

    inventario.vertices.push_back({item, {}});
    return true;
}

static void adicionarAresta(Vertice &origem, int destino, int similaridade) {
    for (Aresta &aresta : origem.adjacentes) {
        if (aresta.destino == destino) {
            aresta.similaridade = similaridade;
            return;
        }
    }

    origem.adjacentes.push_back({destino, similaridade});
}

// Grafo não direcionado: aresta nos dois sentidos
bool inserirSimilaridade(Grafo &inventario, int id1, int id2, int similaridade) {
    if (id1 == id2) {
        return false;
    }

    Vertice *v1 = buscarVertice(inventario, id1);
    Vertice *v2 = buscarVertice(inventario, id2);

    if (v1 == nullptr || v2 == nullptr) {
        return false;
    }

    adicionarAresta(*v1, id2, similaridade);
    adicionarAresta(*v2, id1, similaridade);
    return true;
}

static void imprimirAresta(const Vertice &v, const Vertice &w, int similaridade) {
    cout << v.item.nome_item << " (" << v.item.id << ") -- " << w.item.nome_item << " (" << w.item.id << ") | S = " << similaridade << endl;
}

// BFS seguindo o código da aula, usando list como fila
static void buscaEmLargura(const Grafo &inventario, int s, list<int> &marcados) {
    list<int> fila;
    list<int> emFila;

    marcados.push_back(s);
    fila.push_back(s);
    emFila.push_back(s);

    while (!fila.empty()) {
        int v = fila.front();
        const Vertice *vertice_v = buscarVertice(inventario, v);

        for (const Aresta &aresta : vertice_v->adjacentes) {
            int w = aresta.destino;
            const Vertice *vertice_w = buscarVertice(inventario, w);

            if (!contem(marcados, w)) {
                imprimirAresta(*vertice_v, *vertice_w, aresta.similaridade);
                marcados.push_back(w);
                fila.push_back(w);
                emFila.push_back(w);
            }
            else if (contem(emFila, w)) {
                imprimirAresta(*vertice_v, *vertice_w, aresta.similaridade);
            }
        }

        fila.pop_front();
        emFila.remove(v);
    }
}

// Percorre todos os componentes do grafo com BFS
void exibirSimilaridadesBFS(const Grafo &inventario) {
    list<int> marcados;

    for (const Vertice &vertice : inventario.vertices) {
        if (!contem(marcados, vertice.item.id)) {
            buscaEmLargura(inventario, vertice.item.id, marcados);
        }
    }
}

void buscarItensSimilares(const Grafo &inventario, int codigo, const string &jogador, int similaridade) {
    const Vertice *origem = buscarVertice(inventario, codigo);

    if (origem == nullptr) {
        cout << "Item não encontrado." << endl;
        return;
    }

    bool encontrou = false;

    for (const Aresta &aresta : origem->adjacentes) {
        const Item &item = buscarVertice(inventario, aresta.destino)->item;
        if (aresta.similaridade > similaridade && item.nome_dono != jogador) {
            cout << "Item: " << item.nome_item << endl;
            cout << "Dono: " << item.nome_dono << endl;
            cout << "ID: " << item.id << endl;
            cout << "Similaridade: " << aresta.similaridade << endl;
            cout << endl;
            encontrou = true;
        }
    }
    if (!encontrou) {
        cout << "Nenhum item encontrado." << endl;
    }
}

void removerVertice(Grafo &inventario, int id) {
    for (Vertice &vertice : inventario.vertices) {
        auto itAresta = vertice.adjacentes.begin();
        while (itAresta != vertice.adjacentes.end()) {
            if (itAresta->destino == id) {
                itAresta = vertice.adjacentes.erase(itAresta);
            }
            else {
                itAresta++;
            }
        }
    }

    auto itVertice = inventario.vertices.begin();
    while (itVertice != inventario.vertices.end()) {
        if (itVertice->item.id == id) {
            itVertice = inventario.vertices.erase(itVertice);
        }
        else {
            itVertice++;
        }
    }
}

// Funções de Árvore Binária de Busca (ordenada por nome_item)

void inserirArvore(NoArvore* &p, Item novo_item) {
    if (p == nullptr) {
        p = new NoArvore;
        p->item = novo_item;
        p->esquerda = nullptr;
        p->direita = nullptr;
    }
    else if (novo_item.nome_item < p->item.nome_item) {
        inserirArvore(p->esquerda, novo_item);
    }
    else {
        inserirArvore(p->direita, novo_item);
    }
}

bool existeItemPorNome(NoArvore* p, const string &nome) {
    if (p == nullptr) {
        return false;
    }
    if (nome == p->item.nome_item) {
        return true;
    }
    if (nome < p->item.nome_item) {
        return existeItemPorNome(p->esquerda, nome);
    }
    return existeItemPorNome(p->direita, nome);
}

void exibirEmOrdem(NoArvore* p) {
    if (p != nullptr) {
        exibirEmOrdem(p->esquerda);
        exibirItem(p->item);
        exibirEmOrdem(p->direita);
    }
}

int contarPropriedade(NoArvore* p, const string &propriedade) {
    if (p == nullptr) {
        return 0;
    }

    int quantidade = 0;

    if (p->item.propriedade_magica == propriedade) {
        quantidade = 1;
    }

    return quantidade + contarPropriedade(p->esquerda, propriedade) + contarPropriedade(p->direita, propriedade);
}

static NoArvore* buscarMenor(NoArvore* &p) {
    if (p->esquerda != nullptr) {
        return buscarMenor(p->esquerda);
    }

    NoArvore* copia = p;
    p = p->direita;
    return copia;
}

bool removerArvore(NoArvore* &p, const string &nome, int id) {
    if (p == nullptr) {
        return false;
    }

    if (nome == p->item.nome_item && id == p->item.id) {
        NoArvore* temp = p;

        if (p->direita == nullptr) {
            p = p->esquerda;
        }
        else if (p->esquerda == nullptr) {
            p = p->direita;
        }
        else {
            temp = buscarMenor(p->direita);
            p->item = temp->item;
        }

        delete temp;
        return true;
    }

    if (nome < p->item.nome_item) {
        return removerArvore(p->esquerda, nome, id);
    }

    return removerArvore(p->direita, nome, id);
}

int removerMenosRaros(Grafo &inventario, NoArvore* &arvore, int r) {
    list<Item> remover;

    for (const Vertice &vertice : inventario.vertices) {
        if (vertice.item.valor_raridade < r) {
            remover.push_back(vertice.item);
        }
    }

    for (const Item &item : remover) {
        removerArvore(arvore, item.nome_item, item.id);
        removerVertice(inventario, item.id);
        cout << "Removido: " << item.nome_item << " (ID " << item.id << ")" << endl;
    }

    return remover.size();
}

void destruirArvore(NoArvore* &p) {
    if (p != nullptr) {
        destruirArvore(p->esquerda);
        destruirArvore(p->direita);
        delete p;
        p = nullptr;
    }
}

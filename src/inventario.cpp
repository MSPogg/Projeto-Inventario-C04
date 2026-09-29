// Arquivo para criar as funcionalidades do menu (funções do 1 ao 8)
#include "inventario.h"
#include <string>
#include <iostream>
#include <list>
#include <stdexcept>

using namespace std;

Raridade classificarRaridade(int valor) {
    if(valor >= 100) {
        return Raridade::Mitico;
    }
    if(valor >= 85) {
        return Raridade::Lendario;
    }
    if(valor >= 60) {
        return Raridade::Epico;
    }
    if(valor >= 30) {
        return Raridade::Raro;
    }
    
    return Raridade::Comum;
}

// Funcao 1 - Inserir Item
// Criado usando apenas uma lista pois o grafo será implementado na EP3

void inserirItem(list<Item> &inventario_provisorio, Item novo_item) {
    inventario_provisorio.push_back(novo_item);
}

// Funcao 2 - Cadastrar similaridade (grafo ponderado com lista de adjacência)

static bool contem(const list<int> &lista, int valor){
    for(int elemento : lista){
        if(elemento == valor){
            return true;
        }
    }
    return false;
}

static Vertice *buscarVertice(Grafo &inventario, int id){
    for(Vertice &vertice : inventario.vertices){
        if(vertice.item.id == id){
            return &vertice;
        }
    }
    return nullptr;
}

static const Vertice *buscarVertice(const Grafo &inventario, int id){
    for(const Vertice &vertice : inventario.vertices){
        if(vertice.item.id == id){
            return &vertice;
        }
    }
    return nullptr;
}

bool existeItem(const Grafo &inventario, int id){
    return buscarVertice(inventario, id) != nullptr;
}

// Insere o item como vértice do grafo, mantendo os vértices ordenados por id
bool inserirVertice(Grafo &inventario, Item item){
    for(auto it = inventario.vertices.begin(); it != inventario.vertices.end(); it++){
        if(it->item.id == item.id){
            return false;
        }
        if(it->item.id > item.id){
            inventario.vertices.insert(it, {item, {}});
            return true;
        }
    }

    inventario.vertices.push_back({item, {}});
    return true;
}

static void adicionarAresta(Vertice &origem, int destino, int similaridade){
    for(Aresta &aresta : origem.adjacentes){
        if(aresta.destino == destino){
            aresta.similaridade = similaridade;
            return;
        }
    }

    origem.adjacentes.push_back({destino, similaridade});
}

// Grafo não direcionado: aresta nos dois sentidos
bool inserirSimilaridade(Grafo &inventario, int id1, int id2, int similaridade){
    if(id1 == id2){
        return false;
    }

    Vertice *v1 = buscarVertice(inventario, id1);
    Vertice *v2 = buscarVertice(inventario, id2);

    if(v1 == nullptr || v2 == nullptr){
        return false;
    }

    adicionarAresta(*v1, id2, similaridade);
    adicionarAresta(*v2, id1, similaridade);
    return true;
}

static void imprimirAresta(const Vertice &v, const Vertice &w, int similaridade){
    cout << v.item.nome_item << " (" << v.item.id << ") -- " << w.item.nome_item << " (" << w.item.id << ") | S = " << similaridade << endl;
}

// BFS seguindo o código da aula, usando list como fila
static void buscaEmLargura(const Grafo &inventario, int s, list<int> &marcados){
    list<int> F;
    list<int> emF;

    marcados.push_back(s);
    F.push_back(s);
    emF.push_back(s);

    while(!F.empty()){
        int v = F.front();
        const Vertice *vertice_v = buscarVertice(inventario, v);

        for(const Aresta &aresta : vertice_v->adjacentes){
            int w = aresta.destino;
            const Vertice *vertice_w = buscarVertice(inventario, w);

            if(!contem(marcados, w)){
                imprimirAresta(*vertice_v, *vertice_w, aresta.similaridade);
                marcados.push_back(w);
                F.push_back(w);
                emF.push_back(w);
            }
            else if(contem(emF, w)){
                imprimirAresta(*vertice_v, *vertice_w, aresta.similaridade);
            }
        }

        F.pop_front();
        emF.remove(v);
    }
}

// Percorre todos os componentes do grafo com BFS
void exibirSimilaridadesBFS(const Grafo &inventario){
    list<int> marcados;

    for(const Vertice &vertice : inventario.vertices){
        if(!contem(marcados, vertice.item.id)){
            buscaEmLargura(inventario, vertice.item.id, marcados);
        }
    }
}

void buscarItensSimilares(const Grafo &inventario, int codigo, const string &jogador, int similaridade){
    const Vertice *origem = buscarVertice(inventario, codigo);

    if(origem == nullptr){
        cout << "Item nao encontrado." << endl;
        return;
    }
    
    bool encontrou = false;

    for(const Aresta &aresta : origem->adjacentes){
        const Item &item = buscarVertice(inventario, aresta.destino)->item;
        if(aresta.similaridade > similaridade && item.nome_dono != jogador){
            cout << "Item: " << item.nome_item << endl;
            cout << "Dono: " << item.nome_dono << endl;
            cout << "ID: " << item.id << endl;
            cout << "Similaridade: " << aresta.similaridade << endl;
            cout << endl;
            encontrou = true;
        }
    }
    if(!encontrou){
        cout << "Nenhum item encontrado." << endl;
    }
}

int lerInteiro(const string &mensagem){
    int valor;

    while(true){
        cout << mensagem;

        try{
            if(!(cin >> valor)){
                throw invalid_argument("Entrada inválida");
            }

            return valor;
        }
        catch(const invalid_argument &erro){
            cout << erro.what() << ": digite um número inteiro." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}
// Arquivo para criar as funcionalidades do menu (funções do 1 ao 8)
#include "inventario.h"
#include <string>
#include <iostream>
#include <list>

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
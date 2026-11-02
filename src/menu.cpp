#include "menu.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void limparTela() {
    system("cls");
}

void esperar() {
    system("pause");
}

void topoMenu(){
    cout << AMARELO << "╔══════════════════════════════════════════╗" << RESET << endl;
    cout << AMARELO << "║" << NEGRITO << "        ⚔  INVENTÁRIO DO HERÓI  ⚔         " << RESET << AMARELO << "║" << RESET << endl;
    cout << AMARELO << "╚══════════════════════════════════════════╝" << RESET << endl;
    cout << CINZA << "      ~ que a sorte guie seus saques ~" << RESET << endl << endl;
}

static void mostrarOpcao(int numero, const string &texto){
    cout << "  " << CIANO << "[" << numero << "]" << RESET << " " << texto << endl;
}

void exibirMenu(){
    cout << AMARELO << "  ── O Baú ───────────────────────────────" << RESET << endl;
    mostrarOpcao(1, "Inserir item");
    mostrarOpcao(2, "Cadastrar similaridade entre itens");
    mostrarOpcao(3, "Buscar itens similares");
    mostrarOpcao(4, "Verificar a existência de um item");
    mostrarOpcao(5, "Listar itens (ordem alfabética)");
    mostrarOpcao(6, "Listar itens (ordem de raridade)");
    mostrarOpcao(7, "Contar itens com mesma propriedade mágica");
    mostrarOpcao(8, "Remover itens menos raros");
    cout << AMARELO << "  ────────────────────────────────────────" << RESET << endl;
    cout << "  " << VERMELHO << "[9] Sair da aventura" << RESET << endl << endl;
}
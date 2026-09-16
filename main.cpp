/*
    Projeto por:
    Guilherme Carlos da Silva - 2034
    Murilo Silva Dal Poggetto - 2351
    Yan de Almeida Gonzaga - 874
*/

#include "menu.h"
#include "inventario.h"
#include <iostream>
#include <windows.h>
#include <list>

using namespace std;

// Função temporária
void construcao() {
    cout << "Funcionalidade em construção!" << endl;

    esperar();
    limparTela();
}

int main() {
    // Comandos para saídas de texto em português
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    list<Item> inventario_provisorio;
    int opcao;

    while(true) {
        topoMenu();
        exibirMenu();

        cin >> opcao;

        switch(opcao) {
        // Funcao Inserir Item
        case 1: {
            Item novo_item;
            int valor;

            cin >> novo_item.nome_item;
            cin >> novo_item.nome_dono;
            cin >> novo_item.propriedade_magica;
            cin >> novo_item.id;
            cin >> valor;
            novo_item.raridade = classificarRaridade(valor);


            inserirItem(inventario_provisorio, novo_item);

            break;
        }
        
        case 2:
            construcao();
            break;
            
        case 3:
            construcao();
            break;
        
        case 4:
            construcao();
            break;
        
        case 5:
            construcao();
            break;
        
        case 6:
            construcao();
            break;
        
        case 7:
            construcao();
            break;
        
        case 8:
            construcao();
            break;

        case 9:
            return 0;

        default:
            cout << "Opção inválida!" << endl;
            break;
        }
    }
}
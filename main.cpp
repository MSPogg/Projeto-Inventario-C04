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
#include <string>

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
    treenode* arvore_inventario = nullptr;
    Grafo inventario;
    int opcao;

    while(true) {
        limparTela();
        topoMenu();
        exibirMenu();

        opcao = lerInteiro(AMARELO + "» " + RESET + "Opção: ");

        switch(opcao) {
        // Funcao Inserir Item
        case 1: {
            Item novo_item;
            int valor;

            cout << "Nome do item: ";
            getline(cin, novo_item.nome_item);
            
            cout << "Nome do dono: ";
            getline(cin, novo_item.nome_dono);
            
            cout << "Propriedade mágica: ";
            getline(cin, novo_item.propriedade_magica);
            
            novo_item.id = lerInteiro("ID: ");
            valor = lerInteiro("Valor de raridade: ");
            novo_item.raridade = classificarRaridade(valor);

            if(!inserirVertice(inventario, novo_item)){
                cout << "Já existe um item com o ID " << novo_item.id << "." << endl;
                esperar();
                break;
            }

            tInsert(arvore_inventario, novo_item);

            break;
        }

        case 2: {
            int quantidade = lerInteiro("Quantidade de pares: ");

            for(int i = 0; i < quantidade; i++){
                int id1 = lerInteiro("ID do primeiro item: ");
                int id2 = lerInteiro("ID do segundo item: ");
                int similaridade = lerInteiro("Similaridade: ");

                if(!inserirSimilaridade(inventario, id1, id2, similaridade)){
                    cout << "Par inválido: " << id1 << " " << id2 << endl;
                }
            }

            exibirSimilaridadesBFS(inventario);
            esperar();
            break;
        }
            
        case 3: {
            string jogador;
            cout << "Nome do jogador: ";
            getline(cin, jogador);
            
            int similaridade = lerInteiro("Similaridade mínima: ");
            int codigo = lerInteiro("ID do item: ");

            buscarItensSimilares(inventario, codigo, jogador, similaridade);
            esperar();
            break;
        }
            
        case 4:
            construcao();
            break;

        case 5:
            if(arvore_inventario == nullptr){
                cout << "Inventário vazio!" << endl;
            }
            else {
                tShowInOrder(arvore_inventario);
            }
            esperar();
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
            esperar();
            break;
        }
    }
}
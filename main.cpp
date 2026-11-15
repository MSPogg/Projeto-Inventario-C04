/*
    Projeto por:
    Guilherme Carlos da Silva - 2034
    Murilo Silva Dal Poggetto - 2351
    Yan de Almeida Gonzaga - 874
*/

#include "menu.h"
#include "inventario.h"
#include "arvore_raridade.h"
#include <iostream>
#include <windows.h>
#include <list>
#include <string>

using namespace std;

int main() {
    // Comandos para saídas de texto em português
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    NoArvore *arvore_inventario = nullptr;
    Grafo inventario;
    int opcao;

    while (true) {
        limparTela();
        topoMenu();
        exibirMenu();

        opcao = lerInteiro(AMARELO + "» " + RESET + "Opção: ");

        switch (opcao) {
        // Opção 1 - Inserir item
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

            do {
                valor = lerInteiro("Valor de raridade (0 a 100): ");
                if (valor < 0 || valor > 100) {
                    cout << "A raridade deve ser um valor entre 0 e 100." << endl;
                }
            } while (valor < 0 || valor > 100);

            novo_item.valor_raridade = valor;
            novo_item.raridade = classificarRaridade(valor);

            if (!inserirVertice(inventario, novo_item)) {
                cout << "Já existe um item com o ID " << novo_item.id << "." << endl;
                esperar();
                break;
            }

            inserirArvore(arvore_inventario, novo_item);

            break;
        }

        // Opção 2 - Cadastrar similaridade entre itens
        case 2: {
            int quantidade = lerInteiro("Quantidade de pares: ");

            for (int i = 0; i < quantidade; i++) {
                int id1 = lerInteiro("ID do primeiro item: ");
                int id2 = lerInteiro("ID do segundo item: ");
                int similaridade = lerInteiro("Similaridade: ");

                if (!inserirSimilaridade(inventario, id1, id2, similaridade)) {
                    cout << "Par inválido: " << id1 << " " << id2 << endl;
                }
            }

            exibirSimilaridadesBFS(inventario);
            esperar();
            break;
        }

        // Opção 3 - Buscar itens similares
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

        // Opção 4 - Verificar a existência de um item pelo nome
        case 4: {
            string nome;

            cout << "Digite o nome do item: ";
            getline(cin, nome);

            if (existeItemPorNome(arvore_inventario, nome)) {
                cout << "Item encontrado!" << endl;
            }
            else {
                cout << "Item não encontrado!" << endl;
            }

            esperar();
            break;
        }

        // Opção 5 - Listar itens (ordem alfabética)
        case 5:
            if (arvore_inventario == nullptr) {
                cout << "Inventário vazio!" << endl;
            }
            else {
                exibirEmOrdem(arvore_inventario);
            }
            esperar();
            break;

        // Opção 6 - Listar itens (ordem decrescente de raridade)
        case 6:
            imprimirPorRaridade(inventario);
            esperar();
            break;

        // Opção 7 - Contar itens com mesma propriedade mágica
        case 7: {
            string propriedade;
            cout << "Propriedade mágica: ";
            getline(cin, propriedade);

            int quantidade = contarPropriedade(arvore_inventario, propriedade);
            cout << "Itens com a propriedade \"" << propriedade << "\": " << quantidade << endl;
            esperar();
            break;
        }

        // Opção 8 - Remover itens menos raros
        case 8: {
            int r = lerInteiro("Remover itens com raridade menor que R = ");
            int removidos = removerMenosRaros(inventario, arvore_inventario, r);

            cout << "Total de itens removidos: " << removidos << endl;
            esperar();
            break;
        }

        // Opção 9 - Sair
        case 9:
            destruirArvore(arvore_inventario);
            return 0;

        default:
            cout << "Opção inválida!" << endl;
            esperar();
            break;
        }
    }
}

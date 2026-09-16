#include "menu.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

const string RESET    {"\033[0m"};
const string VERDE    {"\033[32m"}; // Comum
const string AZUL     {"\033[34m"}; // Raro
const string ROXO     {"\033[35m"}; // Épico
const string AMARELO  {"\033[33m"}; // Lendário
const string VERMELHO {"\033[31m"}; // Mítico

void limparTela() {
    system("cls");
}

void esperar() {
    system("pause");
}

void topoMenu() {
    cout << "================== MENU ==================" << endl << endl;
    cout << AMARELO << "           Inventário do Herói            " << RESET << endl << endl;
    cout << "==========================================" << endl << endl;
}

void exibirMenu() {
    cout << "Escolha uma opção:" << endl << endl;
    cout << "[1] Inserir item" << endl;
    cout << "[2] Cadastrar similaridade entre itens" << endl;
    cout << "[3] Buscar itens similares" << endl;
    cout << "[4] Verificar a existência de um item" << endl;
    cout << "[5] Listar itens (ordem alfabética de nome)" << endl;
    cout << "[6] Listar itens (ordem decrescente de raridade)" << endl;
    cout << "[7] Contar itens com mesma propriedade mágica" << endl;
    cout << "[8] Remover itens menos raros" << endl;
    cout << "[9] Sair" << endl << endl;
    cout << "==========================================" << endl << endl;
}
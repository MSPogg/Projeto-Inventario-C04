#include "menu.h"

void menu() {
    std::cout << "================== MENU ==================" << std::endl << std::endl;
    std::cout << "Escolha uma opção:" << std::endl << std::endl;
    std::cout << "a) Inserir item" << std::endl;
    std::cout << "b) Cadastrar similaridade entre itens" << std::endl;
    std::cout << "c) Buscar itens similares" << std::endl;
    std::cout << "d) Verificar a existência de um item" << std::endl;
    std::cout << "e) Listar itens (ordem alfabética de nome)" << std::endl;
    std::cout << "f) Listar itens (ordem decrescente de raridade)" << std::endl;
    std::cout << "g) Contar itens com mesma propriedade mágica" << std::endl;
    std::cout << "h) Remover itens menos raros" << std::endl;
    std::cout << "i) Sair" << std::endl << std::endl;
    std::cout << "===========================================" << std::endl << std::endl;
}
#ifndef MENU_H
#define MENU_H

#include <string>

const std::string RESET    {"\033[0m"};
const std::string NEGRITO  {"\033[1m"};
const std::string CINZA    {"\033[90m"};
const std::string CIANO    {"\033[36m"};
const std::string VERDE    {"\033[32m"}; // Comum
const std::string AZUL     {"\033[34m"}; // Raro
const std::string ROXO     {"\033[35m"}; // Épico
const std::string AMARELO  {"\033[33m"}; // Lendário
const std::string VERMELHO {"\033[31m"}; // Mítico

void limparTela();
void esperar();
void topoMenu();
void exibirMenu();

#endif
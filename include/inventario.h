#ifndef INVENTARIO_H
#define INVENTARIO_H

enum Raridade {
    Comum,
    Raro,
    Epico,
    Lendario,
    Mitico
};

struct Item {
    string nome_item;
    string nome_dono;
    string propriedade_magica;
    int id;
    Raridade raridade;
};

Raridade classificarRaridade(int valor);
void inserirItem(list<Item> &inventario_provisorio, Item novo_item);

#endif
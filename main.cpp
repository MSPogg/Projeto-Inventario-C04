#include "menu.h"
#include <windows.h>
using namespace std;

void construcao() {
    cout << "Funcionalidade em construção!" << endl << endl;
}
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    char opcao;

    while(true) {
        menu();

        cin >> opcao;

        switch(opcao) {
        case 'a':
            construcao();
            break;
        
        case 'b':
            construcao();
            break;
            
        case 'c':
            construcao();
            break;
        
        case 'd':
            construcao();
            break;
        
        case 'e':
            construcao();
            break;
        
        case 'f':
            construcao();
            break;
        
        case 'g':
            construcao();
            break;
        
        case 'h':
            construcao();
            break;

        case 'i':
            return 0;

        default:
            cout << "Opcao invalida!" << endl;
            break;
        }
    }
}
#include "Interfaz.h"
#include <limits>
#include <iomanip>
#include <windows.h>
#include <fstream>
int Interfaz::navegadorPrincipal()
{
    cout << "----------------------------------------" << endl;
    cout << "|  Flecha izquierda / pagina anterior   |" << endl;
    cout << "|  Flecha derecha / pagina siguiente    |" << endl;
    cout << "|  Flecha arriba / pestania siguiente   |" << endl;
    cout << "|  Flecha abajo / pestania anterior     |" << endl;
    cout << "|  Espacio / ir al menu del navegador   |" << endl;
    cout << "----------------------------------------" << endl;

    int opc = -1;

    while (true) {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            opc = 1;
            cout << "Flecha izquierda presionada" << endl;
            system("pause");
            break;
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            opc = 2;
            cout << "Flecha derecha presionada" << endl;
            system("pause");
            break;
        }
        else if (GetAsyncKeyState(VK_UP) & 0x8000) {
            opc = 3;
            cout << "Flecha arriba presionada" << endl;
            system("pause");
            break;
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            opc = 4;
            cout << "Flecha abajo presionada" << endl;
            system("pause");
            break;
        }
        else if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            opc = 5;
            cout << "Espacio presionado, ir al menú del navegador" << endl;
            system("pause");
            break;
           
        }
        else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            opc = 0;
            cout << "Escape presionado, saliendo..." << endl;
            system("pause");
            break;
        }
        Sleep(100);
    }

    if (opc == -1) {
        throw ExcepcionTipo();
    }
    return opc;
}

int Interfaz::menuNavegador()
{
    system("cls");
    string input;
    int opc;
    cout << "----------------------------------------" << endl;
    cout << "|         MENU PRINCIPAL                | " << endl;
    cout << "----------------------------------------" << endl;
    cout << "| 1. Ir al navegador actual             |" << endl;
    cout << "| 2. Navegar a un sitio web             |" << endl;
    cout << "| 3. Agregar un bookmark                |" << endl;
    cout << "| 4. Importar / Exportar Historial      |" << endl;
    cout << "| 5. Mostrar bookmarks                  |" << endl;
    cout << "| 6. Busqueda y filtros                 |" << endl;
    cout << "| 7. Activar / desactivar modo incognito|" << endl;
    cout << "| 8. Nueva pestaña                      |" << endl;
    cout << "| 9. Salir                              |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Ingrese una opcion: ";
    cin >> opc;

    
    if (opc > 9) {
        throw ExcepcionMax(1, 9, opc);
    }
    if (opc < 1) {
        throw ExcepcionMin(1, 9, opc);
    }
    return opc;
}

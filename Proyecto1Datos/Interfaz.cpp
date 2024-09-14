#include "Interfaz.h"
#include <limits>
#include <iomanip>
#include <windows.h>
#include <fstream>



int Interfaz::navegadorPrincipal(Navegador* navegador)
{
    system("cls");
    if (navegador->getListaPestanias() == NULL) {
        cout << "----------------------------------------" << endl;
        cout << "|            No hay pestanias           | " << endl;
        cout << "----------------------------------------" << endl << endl;
    }
    else {
        cout << navegador->getListaPestanias()->toString() << endl;
    }

    cout << "----------------------------------------" << endl;
    cout << "|  Flecha izquierda / pagina anterior   |" << endl;
    cout << "|  Flecha derecha / pagina siguiente    |" << endl;
    cout << "|  Flecha arriba / pestania siguiente   |" << endl;
    cout << "|  Flecha abajo / pestania anterior     |" << endl;
    cout << "|  Espacio / ir al menu del navegador   |" << endl;
    cout << "----------------------------------------" << endl;
    int opc;
 
    int opc2;
    cout << "----------------------------------------" << endl;
    cout << "|                 MENU                  | " << endl;
    cout << "----------------------------------------" << endl;
    cout << "| 1. Navegar a un sitio web             |" << endl;
    cout << "| 2.  Agregar un bookmark               |" << endl;
    cout << "| 3. Importar / Exportar Historial      |" << endl;
    cout << "| 4. Mostrar bookmarks                  |" << endl;
    cout << "| 5. Busqueda y filtros                 |" << endl;
    cout << "| 6. Activar / desactivar modo incognito|" << endl;
    cout << "| 7. Nueva pestaña                      |" << endl;
    cout << "| 8. Salir                              |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Ingrese una opcion: ";
    cin >> opc2;
    while (true) {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            opc = 1;
            cout << "Flecha izquierda presionada" << endl;

            break;
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            opc = 2;
            cout << "Flecha derecha presionada" << endl;

            break;
        }
        else if (GetAsyncKeyState(VK_UP) & 0x8000) {
            opc = 3;
            cout << "Flecha arriba presionada" << endl;

            break;
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            opc = 4;
            cout << "Flecha abajo presionada" << endl;

            break;
        }
        else if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            opc = 5;
            cout << "Espacio presionado, ir al menú del navegador" << endl;

            break;

        }
        else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            opc = 0;
            cout << "Escape presionado, saliendo..." << endl;

            break;
        }
        Sleep(100);
    }
    if (opc2 > 9) {
        throw ExcepcionMax(1, 9, opc2);
    }
    if (opc2 < 1) {
        throw ExcepcionMin(1, 9, opc2);
    }
    if (opc2 == -1) {
        throw ExcepcionTipo();
    }
    return opc2;
}

#include "Interfaz.h"
#include <limits>
#include <iomanip>

int Interfaz::navegadorPrincipal()
{
    
    int opc;
    cout << "----------------------------------------" << endl;
    cout << "|  (1) Pagina anterior                   |" << endl;
    cout << "|  (2) Pagina siguiente                  |" << endl;
    cout << "|  (3) Pestania anterior                 |" << endl;
    cout << "|  (4) Pestania siguiente                |" << endl;
    cout << "|  (5) Ir al menu del navegador          |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Ingrese una opcion: ";

    cin >> opc;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw ExcepcionTipo();
    }
    if (opc > 5) {
        throw ExcepcionMax(1, 5, opc);
    }
    if (opc < 1) {
        throw ExcepcionMin(1, 5, opc);
    }

    return opc;
}

int Interfaz::menuNavegador()
{
    system("cls");
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

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw ExcepcionTipo();
    }
    if (opc > 9) {
        throw ExcepcionMax(1, 9, opc);
    }
    if (opc < 1) {
        throw ExcepcionMin(1, 9, opc);
    }

    return opc;
}

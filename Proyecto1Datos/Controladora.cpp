#include "Controladora.h"
#include <windows.h>

Controladora::Controladora() {
    navegador = new Navegador();
}

Controladora::~Controladora() {
    if (navegador != nullptr) {
        delete navegador;
    }
}


void Controladora::control0() {
   
    
    int opcion = 0;
    do {
        try {
            Interfaz::mostrarNavegador(navegador);
            Sleep(200);
            opcion = Interfaz::detectarTecla();
            switch (opcion) {
            case 1: // Agregar a un sitio web
                break;
            case 2: // Agregar un bookmark
                break;
            case 3: // Importar / Exportar historial
                break;
            case 4: // Mostrar bookmarks
                break;
            case 5: // Busqueda y filtros
                break;
            case 6: // Activar / desactivar modo incógnito
                break;
            case 7: // Nueva pestaña
                control7();
                break;
            case 9: //Ir a pagina anterior
                control8();
                break;
            case 10: //Ir a pagina siguiente
                control9();
                break;
            case 11: //Ir a pestania anterior
                control10();
                break;
            case 12: //Ir a pestania siguiente
                control11();
                break;
            default:
                throw ExcepcionTipo();
            }
        } catch (ExcepcionTipo& ex) {
            cout << "Error: " << ex.what() << endl;
            system("pause");
        } catch (ExcepcionMin& ex) {
            cout << "Error: " << ex.what() << endl;
            system("pause");
        } catch (ExcepcionMax& ex) {
            cout << "Error: " << ex.what() << endl;
            system("pause");
        } catch (...) {
            cout << "Error desconocido." << endl;
            system("pause");
        }
    } while (opcion != 8);
}

// bookmarks
void Controladora::control2()
{
}
// historial importar exportar
void Controladora::control3()
{
}
//mostrar bookmarks
void Controladora::control4()
{
}
// busqueda y filtros
void Controladora::control5()
{
}
// activar desactivar modo incognito
void Controladora::control6()
{
}
// nueva pestaña
void Controladora::control7()
{
    Interfaz::agregarPestania(navegador);
}

// pagina anterior
void Controladora::control8()
{
}
// pagina siguiente
void Controladora::control9()
{
}
// pestaña anterior
void Controladora::control10()
{
    Interfaz::pestaniaAnterior(navegador);
}
// pestaña siguiente
void Controladora::control11()
{
    Interfaz::pestaniaSiguiente(navegador);
}

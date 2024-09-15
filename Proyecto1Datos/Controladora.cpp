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
            Sleep(300);
            opcion = Interfaz::detectarTecla();
            switch (opcion) {
            case 1: // Agregar a un sitio web
                control1();
                break;
            case 2: // Agregar un bookmark
                control2();
                break;
            case 3: // Importar / Exportar historial
                break;
            case 4: // Mostrar bookmarks
                control4();
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
                throw ExcepcionGenerica("Opción no válida, por favor elige otra opción.");
            }
        }
        catch (const ExcepcionGenerica& ex) {

            std::cout << "Error: " << ex.what() << std::endl;
            system("pause");
        }
    } while (opcion != 8);
}

void Controladora::control1()
{
	Interfaz::agregarPaginaWeb(navegador);
}

// bookmarks
void Controladora::control2()
{
    Interfaz::agregarBookmark(navegador);
}
// historial importar exportar
void Controladora::control3()
{
}
//mostrar bookmarks
void Controladora::control4()
{
    Interfaz::mostrarBookmarks(navegador);
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
    Interfaz::paginaAnterior(navegador);
}
// pagina siguiente
void Controladora::control9()
{
    Interfaz::paginaSiguiente(navegador);
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

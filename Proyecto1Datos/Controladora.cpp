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
            case 6: // Activar / desactivar modo inc�gnito
                control6();
                break;
            case 7: // Nueva pesta�a
                control7();
                break;
            case 8: // Nueva pesta�a
                control8();
                break;
            case 9: // salir
                control9();
                break;
            case 10: //Ir a pagina anterior
                control10();
                break;
            case 11: //Ir a pagina siguiente
                control11();
                break;
            case 12: //Ir a pestania anterior
                control12();
                break;
            case 13: //Ir a pestania siguiente
                control13();
                break;
            default:
                throw ExcepcionGenerica("Opcion no valida, por favor elige otra opcion.");
            }
        }
        catch (const ExcepcionGenerica& ex) {

            std::cout << "Error: " << ex.what() << std::endl;
            system("pause");
        }
    } while (opcion != 9);
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
	Interfaz::cambiarModoIncognito(navegador);

}
// nueva pesta�a
void Controladora::control7()
{
    Interfaz::agregarPestania(navegador);
}
//Configuracion de Historial
void Controladora::control8()
{
    int opcion = 0;
    do {
        try {
            Interfaz::menuConfiguraciones();
            Sleep(300);
            opcion = Interfaz::detectarTecla();
            switch (opcion) {
            case 1: // Agregar a un sitio web

                break;
            case 2: // Agregar un bookmark

                break;
            case 3: // Importar / Exportar historial
                break;
            default:
                throw ExcepcionGenerica("Opcion no valida, por favor elige otra opcion.");
            }
        }
        catch (const ExcepcionGenerica& ex) {

            std::cout << "Error: " << ex.what() << std::endl;
            system("pause");
        }
    } while (opcion != 3);
}

//Mensaje de salida
void Controladora::control9()
{
    Interfaz::mensajeSalida();
}

// pagina anterior
void Controladora::control10()
{
    Interfaz::paginaAnterior(navegador);
}
// pagina siguiente
void Controladora::control11()
{
    Interfaz::paginaSiguiente(navegador);
}
// pesta�a anterior
void Controladora::control12()
{
    Interfaz::pestaniaAnterior(navegador);
}
// pesta�a siguiente
void Controladora::control13()
{
    Interfaz::pestaniaSiguiente(navegador);
}


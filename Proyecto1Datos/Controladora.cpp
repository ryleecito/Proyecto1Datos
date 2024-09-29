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
            //Interfaz::mostrarNavegador(navegador);

            opcion = Interfaz::detectarTecla(navegador,1);
            switch (opcion) {
            case 1: // Agregar a un sitio web
                control1();
                break;
            case 2: // Agregar un bookmark
                control2();
                break;
            case 3: // Importar / Exportar historial
                control3();
                break;
            case 4: // Mostrar bookmarks
                control4();
                break;
            case 5: // Busqueda y filtros
                control5();
                break;
            case 6: // Activar / desactivar modo incógnito
                control6();
                break;
            case 7: // Nueva pestaña
                control7();
                break;
            case 8: // Nueva pestaña
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
    int opcion = 0;
    do {
        Interfaz::menuImportarExportar(navegador);
        try {

            Sleep(300);
            opcion = Interfaz::detectarTecla(navegador, 0);
            switch (opcion) {
            case 1: // exportar historial
                control3_1();
                break;
            case 2: // importar historial
                control3_2();
                break;
            case 3:
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
//mostrar bookmarks
void Controladora::control4()
{
    Interfaz::mostrarBookmarks(navegador);
}
// busqueda y filtros
void Controladora::control5()
{
    int opcion = 0;
    do {
        Interfaz::busquedaYFiltros(navegador);
        try {

            Sleep(300);
            opcion = Interfaz::detectarTecla(navegador, 0);
            switch (opcion) {
            case 1: // búsqueda por filtro
                control5_1();
                break;
            case 2: // búsqueda por palabra clave
                control5_2();
                break;
            case 3: // eliminamos filtro
                control5_3();
                break;
            case 4:
                break;
            default:
                throw ExcepcionGenerica("Opcion no valida, por favor elige otra opcion.");
            }
        }
        catch (const ExcepcionGenerica& ex) {
            std::cout << "Error: " << ex.what() << std::endl;
            system("pause");
        }
    } while (opcion != 4);
}
// activar desactivar modo incognito
void Controladora::control6()
{
	Interfaz::cambiarModoIncognito(navegador);

}
// nueva pestaña
void Controladora::control7()
{
    Interfaz::agregarPestania(navegador);
}
//Configuracion de Historial
void Controladora::control8()
{
    int opcion = 0;
    do {
        Interfaz::menuConfiguraciones(navegador);
        try {

            Sleep(300);
            opcion = Interfaz::detectarTecla(navegador, 0);
            switch (opcion) {
            case 1: // cantidad de entradas
                control8_1();
                break;
            case 2: // cantidad de bookmarks
                control8_2();
                break;
            case 3: // reiniciar configs
                control8_3();
                break;
            case 4:
                break;
            default:
                throw ExcepcionGenerica("Opcion no valida, por favor elige otra opcion.");
            }
        }
        catch (const ExcepcionGenerica& ex) {
            std::cout << "Error: " << ex.what() << std::endl;
            system("pause");
        }
    } while (opcion != 4);

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
// pestaña anterior
void Controladora::control12()
{
    Interfaz::pestaniaAnterior(navegador);
}
// pestaña siguiente
void Controladora::control13()
{
    Interfaz::pestaniaSiguiente(navegador);
}

void Controladora::control8_1()
{
    Interfaz::agregarCantidadEntradas(navegador);
}

void Controladora::control8_2()
{
    Interfaz::agregarCantidadTiempo(navegador);
}
void Controladora::control8_3()
{
	Interfaz::quitarConfiguraciones(navegador);
}
// busqueda por filtro
void Controladora::control5_1()
{
    Interfaz::aplicarFiltroNavegador(navegador);
}

// busqueda por palabra clave
void Controladora::control5_2()
{
    Interfaz::busquedaPalabraClave(navegador);
}

void Controladora::control5_3()
{
    Interfaz::eliminarFiltro(navegador);
}

// exportar historial
void Controladora::control3_1()
{
	Interfaz::exportarHistorial(navegador);
}

// importar historial
void Controladora::control3_2()
{
    Navegador* navegador1 = Interfaz::importarHistorial(this->navegador);


    if (navegador1 != nullptr) {
		delete this->navegador;
		this->navegador = navegador1;
	}


}



#pragma once
#define NOMINMAX
#include "Interfaz.h"
#include "Excepciones.h"
#include "Navegador.h"
#include <limits>
#include <sstream>
#include <iostream>
#include <windows.h>




void Interfaz::mostrarNavegador(Navegador* navegador) {

    system("cls");

    if (navegador->getModoIncognito()) {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "|        Modo incognito activado        | " << std::endl;
        std::cout << "----------------------------------------" << std::endl << std::endl;
    }
    else {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "|        Modo incognito desactivado     | " << std::endl;
        std::cout << "----------------------------------------" << std::endl << std::endl;
    }

    if (navegador->cantidadPestanias() == 0) {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "|            No hay pestanias           | " << std::endl;
        std::cout << "----------------------------------------" << std::endl << std::endl;
    }
    else {
       
        std::cout << "Pestania " << navegador->posicionDelIndex() + 1 << std::endl;
        std::cout << navegador->mostrarPestaniaActual() << std::endl;

        //std::cout << navegador->getListaPestanias()->getPestaniaActual()->getHistorial()->toString() << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "|  Flecha izquierda / pagina anterior   |" << std::endl;
    std::cout << "|  Flecha derecha / pagina siguiente    |" << std::endl;
    std::cout << "|  Flecha arriba / pestania siguiente   |" << std::endl;
    std::cout << "|  Flecha abajo / pestania anterior     |" << std::endl;
    std::cout << "|  Espacio / ir al menu del navegador   |" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "|                 MENU                  | " << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "| 1. Navegar a un sitio web             |" << std::endl;
    std::cout << "| 2. Agregar un bookmark                |" << std::endl;
    std::cout << "| 3. Importar / Exportar Historial      |" << std::endl;
    std::cout << "| 4. Mostrar bookmarks                  |" << std::endl;
    std::cout << "| 5. Busqueda y filtros                 |" << std::endl;
    std::cout << "| 6. Activar / desactivar modo incognito|" << std::endl;
    std::cout << "| 7. Nueva pestaña                      |" << std::endl;
    std::cout << "| 8. Configuracion de historial         |" << std::endl;
    std::cout << "| 9. Salir                              |" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Toque tecla para realizar accion: "<<std::endl<<std::endl;

}


int Interfaz::detectarTecla() {
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    DWORD cNumRead;
    INPUT_RECORD irInBuf;
    int tecla = 0;

    while (true) {
        ReadConsoleInput(hConsole, &irInBuf, 1, &cNumRead);

        if (irInBuf.EventType == KEY_EVENT && irInBuf.Event.KeyEvent.bKeyDown) {
            switch (irInBuf.Event.KeyEvent.wVirtualKeyCode) {
            case VK_LEFT:
                tecla = 10; // Código para la tecla de flecha izquierda
                break;
            case VK_RIGHT:
                tecla = 11; // Código para la tecla de flecha derecha
                break;
            case VK_UP:
                tecla = 12; // Código para la tecla de flecha arriba
                break;
            case VK_DOWN:
                tecla = 13; // Código para la tecla de flecha abajo
                break;
            default:
                if (irInBuf.Event.KeyEvent.uChar.AsciiChar >= '1' &&
                    irInBuf.Event.KeyEvent.uChar.AsciiChar <= '9') {
                    tecla = irInBuf.Event.KeyEvent.uChar.AsciiChar - '0'; // Convertir ASCII a número
                }
                break;
            }
            if (tecla != 0) break;
        }
    }
    return tecla;

}

void Interfaz::agregarPestania(Navegador* navegador )
{
    navegador->agregarPestania(new Pestania());
}

void Interfaz::pestaniaAnterior(Navegador* navegador)
{
    if (navegador->cantidadPestanias() == 0) {
        throw ExcepcionGenerica("Cree una pestania para navegar");
    }
    navegador->pestaniaAnterior();
}

void Interfaz::pestaniaSiguiente(Navegador* navegador)
{
    if (navegador->cantidadPestanias() == 0) {
        throw ExcepcionGenerica("Cree una pestania para navegar");
    }
    navegador->pestaniaSiguiente();
}

void Interfaz::agregarPaginaWeb(Navegador* navegador)
{
    if (navegador->cantidadPestanias() == 0) {
        navegador->agregarPestania(new Pestania());
    }

    if (navegador->cantidadPestanias() == 0) {
        throw ExcepcionGenerica("Cree una pestania para navegar");
    }
    std::string url;
    std::cout << " Ingrese la url: ";


    std::cin >> url;


    if (navegador->buscarPaginaWeb(url) != nullptr) {
        navegador->agregarPaginaWeb(navegador->buscarPaginaWeb(url));
	}
	else {
        throw ExcepcionGenerica("404-NotFound");
	}
    system("pause");
 
	
}

void Interfaz::paginaAnterior(Navegador* navegador)
{
    if (navegador->cantidadPestanias() == 0) {
        throw ExcepcionGenerica("Cree una pestania para navegar");
    }
    if ( navegador->cantidadPaginas() == 0) {
        throw ExcepcionGenerica("Realice una busqueda para navegar");
    }
    navegador->paginaAnterior();
    
}

void Interfaz::paginaSiguiente(Navegador* navegador)
{
    if (navegador->cantidadPestanias() == 0) {
        throw ExcepcionGenerica("Cree una pestania para navegar");
    }
    if ( navegador->cantidadPaginas() == 0 ) {
        throw ExcepcionGenerica("Realice una busqueda para navegar");
    }
    navegador->paginaSiguiente();
}

void Interfaz::agregarBookmark(Navegador* navegador)
{
    if (navegador->cantidadPaginas() == 0) {
        throw ExcepcionGenerica("Realice una busqueda para agregar bookmark");
    }
    if (navegador->getModoIncognito()) {
		throw ExcepcionGenerica("No se pueden agregar bookmarks en modo incognito");
    }
    std::string tag;
    std::cout << " Ingrese un tag: ";
    std::cin >> tag;


    navegador->agregarMarcador(new Marcador(new SitioWeb(*navegador->getSitioActual()), tag));
}

void Interfaz::mostrarBookmarks(Navegador* navegador)
{
    std::cout << navegador->MostrarMarcadoresGuardados();
    system("pause");
}

void Interfaz::cambiarModoIncognito(Navegador* navegador)
{
	navegador->cambiarModoIncognito();
}

void Interfaz::agregarCantidadEntradas(Navegador* navegador)
{
    int opc;
	std::cout << " Ingrese la cantidad de entradas: ";
    std::cin >> opc;
	if (opc < 0) {
		throw ExcepcionGenerica("La cantidad de entradas no puede ser negativa");
	}
    if (std::cin.fail()) { 
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw ExcepcionGenerica("Entrada invalida. Debe ingresar un numero entero.");
    }
	navegador->getListaPestanias()->getPestaniaActual()->getHistorial()->getConfiguraciones()->setMaxEntradas(opc);
	std::cout << " Se ha configurado la cantidad de entradas a: " << opc << std::endl;
    system("pause");

}

void Interfaz::agregarCantidadTiempo(Navegador* navegador)
{
    int opc;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << " 6 horas = 360 minutos" << std::endl;
    std::cout << " 12 horas = 720 minutos" << std::endl;
    std::cout << " 24 horas = 1440 minutos" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << " Ingrese la cantidad de minutos para el tiempo de entrada del navegador: ";

    std::cin >> opc;
    if (opc < 0) {
        throw ExcepcionGenerica("La cantidad de entradas no puede ser negativa");
    }
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw ExcepcionGenerica("Entrada invalida. Debe ingresar un numero entero.");
    }
    system("pause");
    /* navegador->getListaPestanias()->getPestaniaActual()->getHistorial()*/
    std::cout << " Se ha agregado la cantidad de tiempo a: " << opc << std::endl;
    system("pause");
}


void Interfaz::menuConfiguraciones(Navegador* navegador)
{
    if (navegador->getListaPestanias()->getPestaniaActual() == NULL) {
        throw ExcepcionGenerica("Error: Cree una pestania primero para configurar su historial");
    
    }
    system("cls");
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "|         MENU DE CONFIGURACION         | " << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "| 1. Configurar cantidad de entradas    |" << std::endl;
    std::cout << "| 2. Configurar tiempo de entradas      |" << std::endl;
    std::cout << "| 3. Regresar                           |" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Toque tecla para realizar accion: " << std::endl << std::endl;
}

void Interfaz::busquedaYFiltros(Navegador* navegador)
{
    if (navegador->getListaPestanias()->getPestaniaActual() == NULL) {
        throw ExcepcionGenerica("Error: Cree una pestania primero para configurar su historial");
    }
    system("cls");
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "|       MENU BUSQUEDA Y FILTROS         | " << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "| 1. Anadir un filtro al navegador      |" << std::endl;
    std::cout << "| 2. Buscar paginas web por nombre      |" << std::endl;
    std::cout << "| 3. Regresar                           |" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Toque tecla para realizar accion: " << std::endl << std::endl;
}

void Interfaz::busquedaPalabraClave(Navegador* navegador)
{
    std::string opc;
    int contador = 1;
    std::cout << " Ingrese la palabra clave para hacer su busqueda:";
    std::cin >> opc;
    for (SitioWeb* sitio : navegador->getListaPestanias()->getPestaniaActual()->getHistorial()->filtrarPaginasPorNombre(opc)) {
        std::cout << "------------------------------------------------------" << std::endl;
		std::cout << " COINCIDENCIA # " << contador << std::endl;
        std::cout << sitio->toString() << std::endl;
        contador++;
        std::cout << "------------------------------------------------------" << std::endl;
    }
    system("pause");
}

void Interfaz::aplicarFiltroNavegador(Navegador* navegador)
{
    std::string opc;
    std::cout << " Ingrese la palabra clave para aplicarle el filtro al navegador:";
    std::cin >> opc;

}

void Interfaz::mensajeSalida()
{
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "|  GRACIAS POR NAVEGAR CON NOSOTROS :)  | " << std::endl;
    std::cout << "----------------------------------------" << std::endl << std::endl;
}




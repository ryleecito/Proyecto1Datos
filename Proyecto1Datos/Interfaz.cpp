
#pragma once
#define NOMINMAX 
#include "Interfaz.h"
#include "Excepciones.h"
#include "Navegador.h"
#include <sstream>
#include <iostream>
#include <windows.h>
#include <limits> 




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

        std::cout << navegador->getListaPestanias()->getPestaniaActual()->getHistorial()->toString() << std::endl;
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
    std::cout << "| 8. Salir                              |" << std::endl;
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
                tecla = 9; // Código para la tecla de flecha izquierda
                break;
            case VK_RIGHT:
                tecla = 10; // Código para la tecla de flecha derecha
                break;
            case VK_UP:
                tecla = 11; // Código para la tecla de flecha arriba
                break;
            case VK_DOWN:
                tecla = 12; // Código para la tecla de flecha abajo
                break;
            default:
                if (irInBuf.Event.KeyEvent.uChar.AsciiChar >= '1' &&
                    irInBuf.Event.KeyEvent.uChar.AsciiChar <= '8') {
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
        std::cout << " 404 - Not Found " << std::endl;
	}
    system("pause");
 
	
}

void Interfaz::paginaAnterior(Navegador* navegador)
{
    if (navegador->cantidadPaginas() == 0) {
        throw ExcepcionGenerica("Realice una busqueda para navegar");
    }
    navegador->paginaAnterior();
    
}

void Interfaz::paginaSiguiente(Navegador* navegador)
{
    if (navegador->cantidadPaginas() == 0) {
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




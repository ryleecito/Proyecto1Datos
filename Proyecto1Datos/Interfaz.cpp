
#pragma once
#define NOMINMAX
#include "Interfaz.h"
#include "Excepciones.h"
#include "Navegador.h"
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
    std::cout << "| 7. Nueva pestania                     |" << std::endl;
    std::cout << "| 8. Configuracion de historial         |" << std::endl;
    std::cout << "| 9. Salir                              |" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Toque tecla para realizar accion: "<<std::endl<<std::endl;

}


int Interfaz::detectarTecla(Navegador* navegador, bool mainMenu) {
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD irInBuf[128];
    DWORD cNumRead;
    int tecla = 0;

    if (mainMenu) {
        mostrarNavegador(navegador);
    }

    while (true) {

        if (navegador->getSitioActual()) {
            if (navegador->limpiarViejasEntradas() && mainMenu) {
                mostrarNavegador(navegador);
            }
        }

        DWORD numEvents = 0;
        if (GetNumberOfConsoleInputEvents(hConsole, &numEvents) && numEvents > 0) {

            if (PeekConsoleInput(hConsole, irInBuf, 128, &cNumRead)) {
                for (DWORD i = 0; i < cNumRead; i++) {
                    if (irInBuf[i].EventType == KEY_EVENT && irInBuf[i].Event.KeyEvent.bKeyDown) {
                        switch (irInBuf[i].Event.KeyEvent.wVirtualKeyCode) {
                        case VK_LEFT: tecla = 10; break;
                        case VK_RIGHT: tecla = 11; break;
                        case VK_UP: tecla = 12; break;
                        case VK_DOWN: tecla = 13; break;
                        default:

                            if (irInBuf[i].Event.KeyEvent.uChar.AsciiChar >= '1' &&
                                irInBuf[i].Event.KeyEvent.uChar.AsciiChar <= '9') {
                                tecla = irInBuf[i].Event.KeyEvent.uChar.AsciiChar - '0';
                            }
                            break;
                        }
                        if (tecla != 0) {
                            FlushConsoleInputBuffer(hConsole); 
                            return tecla; 
                        }
                    }
                }
            }
        }

        Sleep(50); 
    }
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
    std::cout << " Ingrese la URL: ";
    std::cin >> url;

    SitioWeb* sitio = navegador->buscarPaginaWeb(url);

    if (sitio != nullptr) {

       navegador->agregarPaginaWeb(new SitioWeb(*sitio));
       
    }
    else {
        throw ExcepcionGenerica("404 - Not Found");
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
	if (navegador->getModoIncognito() == true) {
		throw ExcepcionGenerica("No se pueden agregar bookmarks en modo incognito");
	}
    if (navegador->cantidadPaginas() == 0) {
        throw ExcepcionGenerica("Realice una busqueda para agregar bookmark");
    }
    if (navegador->getModoIncognito()) {
		throw ExcepcionGenerica("No se pueden agregar bookmarks en modo incognito");
    }
    std::string tag;
    std::cout << " Ingrese un tag: ";
    std::cin >> tag;
    
    Marcador* marcadorExistente = navegador->buscarMarcadorPorSitio(navegador->getSitioActual());
    if (marcadorExistente) {
        marcadorExistente->anadirEtiqueta(tag);
    }
    else {
        navegador->agregarMarcador(new Marcador(new SitioWeb(*navegador->getSitioActual()), tag));
    }
    
}

void Interfaz::mostrarBookmarks(Navegador* navegador)
{
    if (navegador->getModoIncognito() == true) {
        throw ExcepcionGenerica("No se pueden agregar bookmarks en modo incognito");
    }
    std::cout << navegador->MostrarMarcadoresGuardados();
    system("pause");
}

void Interfaz::cambiarModoIncognito(Navegador* navegador)
{
	navegador->cambiarModoIncognito();
}

void Interfaz::agregarCantidadEntradas(Navegador* navegador)
{
    if (navegador->getModoIncognito() == true) {
        throw ExcepcionGenerica("No se pueden agregar bookmarks en modo incognito");
    }
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
	navegador->setMaxEntradas(opc);
    navegador->ajustarTamanoHistorial();

    system("pause");
}

void Interfaz::agregarCantidadTiempo(Navegador* navegador)
{
    if (navegador->getModoIncognito() == true) {
        throw ExcepcionGenerica("No se pueden agregar bookmarks en modo incognito");
    }
    int opc;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << " 5 minutos = 300 segundos" << std::endl;
    std::cout << " 10 minutos = 600 segundos" << std::endl;
    std::cout << " 30 minutos = 1800 segundos  " << std::endl;

    std::cout << "----------------------------------------" << std::endl;
    std::cout << " Ingrese la cantidad de segundos para el timeStamp del navegador: ";

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
	navegador->setTiempoMaximo(opc);

    if (navegador->getSitioActual()) {
       navegador->limpiarViejasEntradas();
    }
   
    std::cout << " Se ha agregado la cantidad de tiempo a: " << opc << std::endl;
    system("pause");
}


void Interfaz::menuConfiguraciones(Navegador* navegador)
{
    if (navegador->getModoIncognito() == true) {
        throw ExcepcionGenerica("No se pueden agregar bookmarks en modo incognito");
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
    if (navegador->getModoIncognito() == true) {
        throw ExcepcionGenerica("No se pueden agregar bookmarks en modo incognito");
    }
    system("cls");
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "|       MENU BUSQUEDA Y FILTROS               | " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "| 1. Buscar paginas web por filtro            |" << std::endl;
    std::cout << "| 2. Buscar paginas web por nombre exacto     |" << std::endl;
    std::cout << "| 3. Eliminar filtro anadido                  |" << std::endl;
    std::cout << "| 4. Regresar                                 |" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "Toque tecla para realizar accion: " << std::endl << std::endl;
}

void Interfaz::busquedaPalabraClave(Navegador* navegador)
{
    if (navegador->getModoIncognito() == true) {
        throw ExcepcionGenerica("No se pueden agregar bookmarks en modo incognito");
    }
    std::string opc;
    int contador = 1;
    std::cout << " Ingrese la palabra clave para hacer la busqueda:";
    std::cin >> opc;
    std::cout<<navegador->busquedaPalabraClave(opc);
    system("pause");
    
}

void Interfaz::aplicarFiltroNavegador(Navegador* navegador)
{
    if (navegador->getModoIncognito() == true) {
        throw ExcepcionGenerica("No se pueden agregar bookmarks en modo incognito");
    }
    std::string opc;
    std::cout << " Ingrese la palabra clave para aplicarle el filtro al navegador:";
    std::cin >> opc;
    navegador->getListaPestanias()->getHistorial()->setFiltro(opc);
    navegador->getListaPestanias()->getHistorial()->moverseAPrimeraCoincidencia();
	system("pause");
}


void Interfaz::menuImportarExportar(Navegador* navegador)
{
    if (navegador->getModoIncognito() == true) {
        throw ExcepcionGenerica("No se pueden agregar bookmarks en modo incognito");
    }
    system("cls");
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "| 1. Exportar historial (con sus bookmarks) |" << std::endl;
    std::cout << "| 2. Importar historial (con sus bookmarks) |" << std::endl;
    std::cout << "| 3. Regresar                               |" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Toque tecla para realizar accion: " << std::endl << std::endl;
    
}

void Interfaz::importarHistorial(Navegador* navegador)
{
    if (navegador->getModoIncognito() == true) {
        throw ExcepcionGenerica("No se pueden agregar bookmarks en modo incognito");
    }
    std::string opc;
    std::cout << "Ingrese el nombre de la sesion que quiere importar al navegador: ";
    std::cin >> opc;

    std::ifstream archivo(opc, std::ios::binary);
    if (!archivo) {
        throw ExcepcionGenerica("Error: No se ha podido abrir el archivo, verifique el nombre de la sesion");
    }


    Navegador* navegadorCargado = Navegador::cargarArchivoNavegador(archivo);
    if (navegadorCargado) {
        delete navegador; 
        navegador = navegadorCargado; 
        std::cout << "Se ha importado el historial con exito." << std::endl;
        system("pause");
    }
    else {
        throw ExcepcionGenerica("Error: No se ha podido importar el historial correctamente.");
    }

    archivo.close(); 
    
}

void Interfaz::exportarHistorial(Navegador* navegador)
{
    if (navegador->getModoIncognito() == true) {
        throw ExcepcionGenerica("No se pueden agregar bookmarks en modo incognito");
    }
    std::string opc;
    std::cout << "Ingrese el nombre con el que quiere guardar la sesion: ";
    std::cin >> opc;

    std::ofstream archivo(opc, std::ios::binary); 
    if (!archivo) {
        throw ExcepcionGenerica("Error: No se ha podido crear el archivo.");
		system("pause");
    }
    navegador->guardarArchivoNavegador(archivo);
    std::cout << "Se ha exportado el historial con exito." << std::endl;
	system("pause");
    archivo.close(); 
   
}

void Interfaz::limpiarViejasEntradas(Navegador* navegador)
{
    if (navegador->getModoIncognito() == true) {
        throw ExcepcionGenerica("No se pueden agregar bookmarks en modo incognito");
    }
    navegador->limpiarViejasEntradas();
	std::cout << "Se han limpiado las entradas antiguas con exito." << std::endl;
	system("pause");
}

void Interfaz::eliminarFiltro(Navegador* navegador)
{
	navegador->getListaPestanias()->getHistorial()->setFiltro("");
}

void Interfaz::mensajeSalida()
{
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "|  GRACIAS POR NAVEGAR CON NOSOTROS :)  | " << std::endl;
    std::cout << "----------------------------------------" << std::endl << std::endl;
}





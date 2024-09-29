#pragma once
#define NOMINMAX
#include "Navegador.h"
#include <windows.h>

class Interfaz
{
    public:

        static void mostrarNavegador(Navegador* navegador);

        static int detectarTecla(Navegador* navegador, bool tipoMenu);

        static void agregarPestania(Navegador* navegador);
        
        static void pestaniaAnterior(Navegador* navegador);

        static void pestaniaSiguiente(Navegador* navegador);

		static void agregarPaginaWeb(Navegador* navegador);

        static void paginaAnterior(Navegador* navegador);

        static void paginaSiguiente(Navegador* navegador);

        static void agregarBookmark(Navegador* navegador);

        static void mostrarBookmarks(Navegador* navegador);

		static void cambiarModoIncognito(Navegador* navegador);
        
		static void agregarCantidadEntradas(Navegador* navegador);

		static void agregarCantidadTiempo(Navegador* navegador);

        static void menuConfiguraciones(Navegador* navegador);

		static void busquedaYFiltros(Navegador* navegador);

		static void busquedaPalabraClave(Navegador* navegador); 

		static void aplicarFiltroNavegador(Navegador* navegador);

		static void menuImportarExportar(Navegador* navegador);

		static Navegador* importarHistorial(Navegador* navegador);

		static void exportarHistorial(Navegador* navegador);

		static void eliminarFiltro(Navegador* navegador);

		static void quitarConfiguraciones(Navegador* navegador);
   
        static void mensajeSalida();

};



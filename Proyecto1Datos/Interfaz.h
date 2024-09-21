#pragma once
#include "Excepciones.h"
#include "Navegador.h"
#include <sstream>
#include <iostream>


class Interfaz
{
    public:

        static void mostrarNavegador(Navegador* navegador);

        static int detectarTecla();

        static void agregarPestania(Navegador* navegador);
        
        static void pestaniaAnterior(Navegador* navegador);

        static void pestaniaSiguiente(Navegador* navegador);

		static void agregarPaginaWeb(Navegador* navegador);

        static void paginaAnterior(Navegador* navegador);

        static void paginaSiguiente(Navegador* navegador);

        static void agregarBookmark(Navegador* navegador);

        static void mostrarBookmarks(Navegador* navegador);

		static void cambiarModoIncognito(Navegador* navegador);

        static void menuConfiguraciones();
   
        static void mensajeSalida();

};


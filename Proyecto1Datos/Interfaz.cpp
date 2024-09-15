
#pragma once
#include "Interfaz.h"
#include "Excepciones.h"
#include "Navegador.h"
#include <sstream>
#include <iostream>
#include <windows.h>

using namespace std;




void Interfaz::mostrarNavegador(Navegador* navegador) {

    system("cls");
    if (navegador->cantidadPestanias()==0) {
        cout << "----------------------------------------" << endl;
        cout << "|            No hay pestanias           | " << endl;
        cout << "----------------------------------------" << endl << endl;
    }
    else {

        cout << "Pestania "<<navegador->posicionDelIndex()+1<< endl;
        cout << navegador->mostrarPestaniaActual() << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << "|  Flecha izquierda / pagina anterior   |" << endl;
    cout << "|  Flecha derecha / pagina siguiente    |" << endl;
    cout << "|  Flecha arriba / pestania siguiente   |" << endl;
    cout << "|  Flecha abajo / pestania anterior     |" << endl;
    cout << "|  Espacio / ir al menu del navegador   |" << endl;
    cout << "----------------------------------------" << endl;
    int opc2;
    int opc2;
    int opc2;
    int opc2;
    cout << "----------------------------------------" << endl;
    cout << "|                 MENU                  | " << endl;
    cout << "----------------------------------------" << endl;
    cout << "| 1. Navegar a un sitio web             |" << endl;
    cout << "| 2. Agregar un bookmark                |" << endl;
    cout << "| 3. Importar / Exportar Historial      |" << endl;
    cout << "| 4. Mostrar bookmarks                  |" << endl;
    cout << "| 5. Busqueda y filtros                 |" << endl;
    cout << "| 6. Activar / desactivar modo incognito|" << endl;
    cout << "| 7. Nueva pestaña                      |" << endl;
    cout << "| 8. Salir                              |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Toque tecla para realizar accion: ";

}

int Interfaz::detectarTecla() {
    while (true)
    {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            return 9;
            Sleep(200);
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            return 10;
            Sleep(200);
        }
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            return 11;
            Sleep(200);
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            return 12;
            Sleep(200);
        }

        for (int i = 0x31; i <= 0x38; i++) {  // Teclas numéricas del 1 al 8
            if (GetAsyncKeyState(i) & 0x8000) {
                return i - 0x30;
                Sleep(200);
            }
        }
      
    }

    return 0;

}

void Interfaz::agregarPestania(Navegador* navegador )
{
    navegador->agregarPestania(new Pestania());
}

void Interfaz::pestaniaAnterior(Navegador* navegador)
{
    navegador->pestaniaAnterior();
}

void Interfaz::pestaniaSiguiente(Navegador* navegador)
{
    navegador->pestaniaSiguiente();
}




#include "AdminHistorial.h"

AdminHistorial::AdminHistorial()
{
	maxEntradas = 0;
}

AdminHistorial::AdminHistorial(int maxEntradas)
{
	this->maxEntradas = maxEntradas;
}

AdminHistorial::~AdminHistorial()
{
}

void AdminHistorial::limpiarEntradasAntiguas(Historial* historial)
{
    while (historial->getpilaAtras().size() > maxEntradas) {
        stack<SitioWeb*> tempStack;
        stack<SitioWeb*> pilaAtras = historial->getpilaAtras();
        while (pilaAtras.size() > 1) {
            tempStack.push(pilaAtras.top());
            pilaAtras.pop();
        }
        delete pilaAtras.top();
        pilaAtras.pop();
        while (!tempStack.empty()) {
            pilaAtras.push(tempStack.top());
            tempStack.pop();
        }
    }
}

void AdminHistorial::setMaxEntradas(int maxEntradas)
{
	this->maxEntradas = maxEntradas;
}

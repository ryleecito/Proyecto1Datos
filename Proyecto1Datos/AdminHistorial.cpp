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
    while (historial->getHistorial().size() > maxEntradas) {
      
        std::deque<SitioWeb*> historialList = historial->getHistorial();
        while (historialList.size() > maxEntradas) {
            SitioWeb* sitioAntiguo = historialList.front();  
            historialList.pop_front();
            delete sitioAntiguo; 
        }
    }
}

void AdminHistorial::setMaxEntradas(int maxEntradas)
{
	this->maxEntradas = maxEntradas;
}

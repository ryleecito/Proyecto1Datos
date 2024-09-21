#include "ConfigHistorial.h"

ConfigHistorial::ConfigHistorial()
{
	maxEntradas = -1;
}

ConfigHistorial::ConfigHistorial(int maxEntradas)
{
	this->maxEntradas = maxEntradas;
}

ConfigHistorial::~ConfigHistorial()
{
}

//void AdminHistorial::limpiarEntradasAntiguas(Historial* historial)
//{
//    while (historial->getHistorial().size() > maxEntradas) {
//      
//        std::list<SitioWeb*> historialList = historial->getHistorial();
//        while (historialList.size() > maxEntradas) {
//            SitioWeb* sitioAntiguo = historialList.front();  
//            historialList.pop_front();
//            delete sitioAntiguo; 
//        }
//    }
//}

void ConfigHistorial::setMaxEntradas(int maxEntradas)
{
	this->maxEntradas = maxEntradas;
}

int ConfigHistorial::getMaxEntradas()
{
	return maxEntradas;
}

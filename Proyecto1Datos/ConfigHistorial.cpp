#include "ConfigHistorial.h"

ConfigHistorial::ConfigHistorial()
{
	maxEntradas = -1;
}

ConfigHistorial::ConfigHistorial(const ConfigHistorial&)
{
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

void ConfigHistorial::guardarArchivoConfigHistorial(std::ofstream& out)
{
	out.write(reinterpret_cast<const char*>(&maxEntradas), sizeof(maxEntradas));
}

ConfigHistorial* ConfigHistorial::cargarArchivoConfigHistorial(std::ifstream& in)
{
	ConfigHistorial* config = new ConfigHistorial();
	in.read(reinterpret_cast<char*>(&config->maxEntradas), sizeof(config->maxEntradas)); 
	return config; 
}

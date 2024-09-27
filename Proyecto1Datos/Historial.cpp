#include "Historial.h"
#include "ConfigHistorial.h"
#include <sstream>
#include <algorithm>


Historial::Historial() : posicionActual(historial.end()){
    filtro = "";
}

Historial::~Historial() {
    limpiarHistorial();

}

int Historial::size() const {

    return (int)historial.size();
}

void Historial::add(SitioWeb* sitioWeb) {
    historial.push_back(sitioWeb);
    posicionActual = std::prev(historial.end());

}

void Historial::retroceder() {

    if (historial.empty()) {
        return; // No hacemos nada si el historial está vacío
    }

    if (posicionActual == historial.end()) {
        // Si estamos al final, movemos a la última página
        --posicionActual;
    }
    else if (posicionActual != historial.begin()) {
        // Solo retrocedemos si no estamos al principio
        --posicionActual;
    }

    // Aplicar filtro si es necesario
    while (!filtro.empty() && posicionActual != historial.begin()) {
        if ((*posicionActual)->getTitulo().find(filtro) != std::string::npos ||
            (*posicionActual)->getUrl().find(filtro) != std::string::npos) {
            break; // Encontramos una página que cumple con el filtro
        }
        --posicionActual;
    }
}


void Historial::avanzar() {
    if (posicionActual != std::prev(historial.end())) {
        ++posicionActual;

        // Aplicar filtro si es necesario
        while (!filtro.empty() && posicionActual != historial.end()) {
            if ((*posicionActual)->getTitulo().find(filtro) != std::string::npos ||
                (*posicionActual)->getUrl().find(filtro) != std::string::npos) {
                break; // Encontramos una página que cumple con el filtro
            }

            if (posicionActual == std::prev(historial.end())) {
                break; // Estamos en el último elemento, no avanzamos más
            }

            ++posicionActual;
        }
    }
}



void Historial::limpiarHistorial() {
    for (SitioWeb* sitio : historial) {
        delete sitio;
    }
    historial.clear();
    posicionActual = historial.end();
}




std::list<SitioWeb*> Historial::filtrarPaginasPorNombre(const std::string& nombre) const
{
    std::list<SitioWeb*> paginasFiltradas;
    std::string nombreFiltrado = nombre;
    // convertimos todo el string a minusculas
    transform(nombreFiltrado.begin(), nombreFiltrado.end(), nombreFiltrado.begin(), ::tolower);

    for (SitioWeb* sitio : historial) {
        if (sitio != nullptr) {
            // obtenemos el titulo y lo convertimos a minusculas por cada 
			// sitio web que entramos en el historial
            std::string tituloSitio = sitio->getTitulo();
            transform(tituloSitio.begin(), tituloSitio.end(), tituloSitio.begin(), ::tolower);
            if (tituloSitio.find(nombreFiltrado) != std::string::npos) {
                paginasFiltradas.push_back(sitio);
            }
        }
    }
    return paginasFiltradas;
}

std::list<SitioWeb*> Historial::getHistorial() const {
    return historial;
}

SitioWeb* Historial::getSitioActual() const {
    if (posicionActual != historial.end()) {
        return *posicionActual;
    }
    return nullptr;
}

std::string Historial::toString() const {
    std::stringstream ss;
    ss << "Historial:\n";

    for (const auto sitio : historial) {
        ss << sitio->toString() << "\n";
    }

    return ss.str();
}

void Historial::ajustarTamanoHistorial() {
   
    //while (historial.size() > configuraciones->getMaxEntradas()) {
 
    //    delete historial.front();  
    //    historial.pop_front();  
    //}
    //if (posicionActual == historial.end()) {
    //    posicionActual = --historial.end();
    //}
}

bool Historial::limpiarEntradasViejas() {
    int tiempoMaximo = ConfigHistorial::getInstancia()->getTiempoMaximo();

    // Verificar que el tiempo máximo es válido
    if (tiempoMaximo < 0) {
        return false;
    }

    SitioWeb* sitioActual = getSitioActual();
    bool entradasBorradas = false; // Variable para rastrear si se borraron entradas

    for (auto it = historial.begin(); it != historial.end(); ) {
        SitioWeb* sitio = *it;

        // Calcular la diferencia de tiempo
        double diff = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now() - sitio->getTiempoDeIngreso()
        ).count();

        // Verificar si la entrada es vieja y eliminarla
        if (diff > tiempoMaximo) {
            it = historial.erase(it); // Eliminar la entrada
            entradasBorradas = true; // Marcar que se borró una entrada
        }
        else {
            ++it; // Solo avanzar el iterador si no se borró nada
        }
    }

    
    if (historial.empty()) {
        posicionActual = historial.end();
    }
    else if (posicionActual == historial.end()) {
        posicionActual = --historial.end();
    }
}

std::string Historial::getFiltro()
{
    return filtro;
}

void Historial::setFiltro(std::string filtro)
{
	this->filtro = filtro;
}


void Historial::serializarHistorial(std::ofstream& out)
{
    //if (configuraciones != nullptr) {
    //    configuraciones->guardarArchivoConfigHistorial(out);
    //}

    //size_t size = historial.size();
    //out.write(reinterpret_cast<const char*>(&size), sizeof(size));

    //for (SitioWeb* sitio : historial) {
    //    sitio->guardarArchivoSitioWeb(out);
    //}
}

Historial* Historial::cargarArchivoHistorial(std::ifstream& in)
{
    //Historial* historialCargado = new Historial(); 
    //ConfigHistorial* configuracionCargado = ConfigHistorial::cargarArchivoConfigHistorial(in);
    //historialCargado->setConfiguraciones(configuracionCargado);

    //size_t size;
    //in.read(reinterpret_cast<char*>(&size), sizeof(size));
    //for (size_t i = 0; i < size; ++i) {
    //    SitioWeb* sitio = SitioWeb::cargarArchivoSitioWeb(in);
    //    if (sitio) {
    //        historialCargado->historial.push_back(sitio);
    //    }
    //}
    //historialCargado->posicionActual = historialCargado->historial.end();

    //return historialCargado; 
    return nullptr;
}

std::string Historial::getUrlActual() const
{
    if (posicionActual != historial.end()) {
        return (*posicionActual)->getUrl();
    }
    return "";
}

std::string Historial::getTituloActual() const
{
    if (posicionActual != historial.end()) {
		return (*posicionActual)->getTitulo();
	}
    return "";
}

std::string Historial::getDominioActual() const
{
    if (posicionActual != historial.end()) {
		return (*posicionActual)->getDominio();
	}
	return "";
}

bool Historial::existeSitioWeb(const std::string url)
{

    for (const auto& sitio : historial) {
        if (sitio->getUrl() == url) {
            return true;  
        }
    }
    return false; 
}


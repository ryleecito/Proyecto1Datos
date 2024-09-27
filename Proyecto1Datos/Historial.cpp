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
    filtro = "";

}

void Historial::retroceder() {

    if (historial.empty()) {
        return;
    }

    if (filtro.empty()) {
        if (posicionActual != historial.begin()) {
            --posicionActual;
        }
        return;
    }

    while (posicionActual != historial.begin()) {
        --posicionActual;

        if ((*posicionActual)->getTitulo().find(filtro) != std::string::npos ||
            (*posicionActual)->getUrl().find(filtro) != std::string::npos) {
            break; 
        }
    }
}

void Historial::avanzar() {

    if (historial.empty()) {
        return;
    }


    if (filtro.empty()) {
        if (posicionActual != std::prev(historial.end())) {
            ++posicionActual;
        }
        return;
    }

    if (std::distance(historial.begin(), historial.end()) == 2) {

        if (posicionActual == historial.begin()) {

            ++posicionActual;

            if ((*posicionActual)->getTitulo().find(filtro) == std::string::npos &&
                (*posicionActual)->getUrl().find(filtro) == std::string::npos) {

                posicionActual = historial.begin(); 
            }
        }
        return; 
    }

    while (posicionActual != std::prev(historial.end())) {
        ++posicionActual;


        if ((*posicionActual)->getTitulo().find(filtro) != std::string::npos ||
            (*posicionActual)->getUrl().find(filtro) != std::string::npos) {
            break;
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

    if (tiempoMaximo < 0) {
        return false;
    }

    SitioWeb* sitioActual = getSitioActual();
    bool entradasBorradas = false;

    for (auto it = historial.begin(); it != historial.end(); ) {
        SitioWeb* sitio = *it;

        double diff = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now() - sitio->getTiempoDeIngreso()
        ).count();

        if (diff > tiempoMaximo) {
            it = historial.erase(it); 
            entradasBorradas = true; 
        }
        else {
            ++it; 
        }
    }

    
    if (historial.empty()) {
        posicionActual = historial.end();
    }
    else if (posicionActual == historial.end()) {
        posicionActual = --historial.end();
    }

    return entradasBorradas;
}

std::string Historial::getFiltro()
{
    return filtro;
}

void Historial::setFiltro(std::string filtro)
{
	this->filtro = filtro;
	moverseAPrimeraCoincidencia();
}

// Este metodo lo utilizamos para que cuando agreguemos un filtro,
// el historial se mueva a la primera coincidencia que encuentre
void Historial::moverseAPrimeraCoincidencia()
{
	if (filtro.empty()) {
		return;
	}

	for (auto it = historial.begin(); it != historial.end(); ++it) {
		if ((*it)->getTitulo().find(filtro) != std::string::npos ||
			(*it)->getUrl().find(filtro) != std::string::npos) {
			posicionActual = it;
			break;
		}
    }
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


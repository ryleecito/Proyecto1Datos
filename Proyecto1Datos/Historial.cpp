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

    auto it = std::find_if(historial.begin(), historial.end(),
        [=](SitioWeb* site) { return site->getUrl() == sitioWeb->getUrl(); });

    if (it != historial.end()) {
        delete* it;        
        historial.erase(it); 
    }

    int maxEntradas = ConfigHistorial::getInstancia()->getMaxEntradas();
    if (historial.size() >= maxEntradas) {
        delete historial.front(); 
        historial.pop_front();    
    }


    historial.push_back(sitioWeb);
    posicionActual = std::prev(historial.end());
    filtro = ""; 
}

void Historial::retroceder() {
    if (historial.empty() || posicionActual == historial.begin()) {
        return; 
    }

    if (filtro.empty()) {

        --posicionActual; 
        return;
    }

    auto nuevaPosicion = std::prev(posicionActual);

    while (nuevaPosicion != historial.begin()) {
        if ((*nuevaPosicion)->getTitulo().find(filtro) != std::string::npos ||
            (*nuevaPosicion)->getUrl().find(filtro) != std::string::npos) {
            posicionActual = nuevaPosicion; // Mover a la nueva posición que cumple con el filtro.
            return;
        }
        nuevaPosicion = std::prev(nuevaPosicion); // Retroceder al anterior.
    }

    if ((*historial.begin())->getTitulo().find(filtro) != std::string::npos ||
        (*historial.begin())->getUrl().find(filtro) != std::string::npos) {
        posicionActual = historial.begin(); 
    }
}

void Historial::avanzar() {
    if (historial.empty() || posicionActual == historial.end()) {
        return; 
    }

    if (filtro.empty()) {

        if (posicionActual != prev(historial.end()))
            ++posicionActual;
        return;
    }


    auto nuevaPosicion = std::next(posicionActual);

    while (nuevaPosicion != historial.end()) {

        if ((*nuevaPosicion)->getTitulo().find(filtro) != std::string::npos ||
            (*nuevaPosicion)->getUrl().find(filtro) != std::string::npos) {
            posicionActual = nuevaPosicion;
            return;
        }
        ++nuevaPosicion; 
    }

}



void Historial::limpiarHistorial() {
    for (SitioWeb* sitio : historial) {
        delete sitio;
    }
    historial.clear();
    posicionActual = historial.end();
}

std::string Historial::busquedaPalabraClave(const std::string& palabraClave) const
{
    std::stringstream s;
    int contador = 1;
    std::string palabraFiltrada = palabraClave;

    transform(palabraFiltrada.begin(), palabraFiltrada.end(), palabraFiltrada.begin(), ::tolower);

    for (SitioWeb* sitio : historial) {
        if (sitio != nullptr) {
 
            std::string tituloSitio = sitio->getTitulo();
            transform(tituloSitio.begin(), tituloSitio.end(), tituloSitio.begin(), ::tolower);

            if (tituloSitio.find(palabraFiltrada) != std::string::npos) {
                s << "------------------------------------------------------" << std::endl;
                s << " COINCIDENCIA # " << contador << std::endl;
                s << sitio->toString() << std::endl;
                contador++;
                s << "------------------------------------------------------" << std::endl;
            }
        }
    }

    return s.str(); 
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
    int maxEntradas = ConfigHistorial::getInstancia()->getMaxEntradas();
    bool posicionActualEliminada = false;
    filtro = "";

    while (historial.size() > maxEntradas) {
        if (posicionActual == historial.begin()) {
            posicionActualEliminada = true;
        }

        delete historial.front();
        historial.pop_front();

        if (posicionActual == historial.begin()) {

            ++posicionActual;
        }
    }

    if (historial.empty()) {
        posicionActual = historial.end();
        return; 
    }

    if (posicionActualEliminada || posicionActual == historial.end()) {
        posicionActual = --historial.end(); // Mover a la última posición válida del historial.
    }
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
    
    if (posicionActual == historial.end()) {
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
	
}

void Historial::moverseAPrimeraCoincidencia() {
    if (filtro.empty()) {
        return;  // No hay filtro, no se hace nada
    }

    // Variable para controlar si encontramos una coincidencia
    bool coincidenciaEncontrada = false;

    // Recorrer el historial buscando coincidencias
    for (auto it = historial.begin(); it != historial.end(); ++it) {
        if ((*it)->getTitulo().find(filtro) != std::string::npos ||
            (*it)->getUrl().find(filtro) != std::string::npos) {
            posicionActual = it;  // Ajustar posicionActual a la coincidencia
            coincidenciaEncontrada = true;  // Marcamos que encontramos una coincidencia
            break;  // Salir del bucle al encontrar la primera coincidencia
        }
    }

    // Si no se encontró ninguna coincidencia, ajustar a end
    if (!coincidenciaEncontrada) {
        posicionActual = historial.end();  // Ajustar a end si no hay coincidencias
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

Historial* Historial::deserializar(std::ifstream& in)
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





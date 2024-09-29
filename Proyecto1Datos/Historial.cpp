#include "Historial.h"
#include "ConfigHistorial.h"
#include <sstream>
#include <algorithm>


Historial::Historial() : posicionActual(historial.end()), filtro("") {
}

Historial::~Historial() {
    limpiarHistorial();
}

int Historial::size() const {

    return (int)historial.size();
}

void Historial::add(SitioWeb* sitioWeb) {

    if (historial.empty()) {
        historial.push_back(new SitioWeb(*sitioWeb));
        posicionActual = std::prev(historial.end());
        filtro = "";
        return;
    }

    eliminarSitioSiExiste(sitioWeb);

    int maxEntradas = ConfigHistorial::getInstancia()->getMaxEntradas();

    if (historial.size() >= maxEntradas) {
        delete historial.front();
        historial.pop_front();
    }

    historial.push_back(new SitioWeb(*sitioWeb));
    posicionActual = std::prev(historial.end());
    filtro = "";
}

bool Historial::existeSitio(SitioWeb* site) {

    for (const auto& sitio : historial) {
        if (sitio->getUrl() == site->getUrl()) {
            return true; 
        }
    }
    return false; 
}

void Historial::eliminarSitioSiExiste(SitioWeb* site) {

    if (!existeSitio(site)) {
        return; 
    }

    for (auto iter = historial.begin(); iter != historial.end(); ++iter) {
        if ((*iter)->getUrl() == site->getUrl()) { 
            delete* iter;
            historial.erase(iter);
            return;
        }
    }
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
            posicionActual = nuevaPosicion; 
            return;
        }
        nuevaPosicion = std::prev(nuevaPosicion); 
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

    if (historial.empty()) {
        return;
    }

    int maxEntradas = ConfigHistorial::getInstancia()->getMaxEntradas();
    bool posicionActualEliminada = false;

    if (maxEntradas <= 0) {
        return;
    }

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
        posicionActual = --historial.end(); 
    }
}

bool Historial::limpiarEntradasViejas() {
    if (historial.empty()) {
        return false; // Si el historial está vacío, no hay entradas que limpiar
    }

    int tiempoMaximo = ConfigHistorial::getInstancia()->getTiempoMaximo();
    if (tiempoMaximo <= 0) {
        return false; // Si el tiempo máximo es cero o negativo, no se eliminan entradas
    }

    bool entradasBorradas = false;

    // Guardamos la posición original de posicionActual
    auto posicionOriginal = posicionActual;

    // Iterador para recorrer el historial
    for (auto it = historial.begin(); it != historial.end(); ) {
        SitioWeb* sitio = *it;

        // Calcular la diferencia de tiempo
        double diff = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now() - sitio->getTiempoDeIngreso()
        ).count();

        if (diff > tiempoMaximo) {
            delete sitio;         // Eliminar el sitio web
            it = historial.erase(it); // Borrar el sitio del historial
            entradasBorradas = true;  // Marcar que se borró una entrada
        }
        else {
            ++it; // Solo avanzar si no se borró nada
        }
    }

    // Actualizar posicionActual
    if (historial.empty()) {
        posicionActual = historial.end(); // Si el historial está vacío, se ajusta la posición
    }
    else if (posicionActual == historial.end() || posicionActual == posicionOriginal) {
        posicionActual = --historial.end(); // Si estaba en el final o fue borrada, ajustamos a la última entrada
    }

    return entradasBorradas; // Retornar si se borraron entradas
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
    
    if (historial.empty()) {
        return;
    }

    if (filtro.empty()) {
        return;  
    }

    bool coincidenciaEncontrada = false;

    for (auto it = historial.begin(); it != historial.end(); ++it) {
        if ((*it)->getTitulo().find(filtro) != std::string::npos ||
            (*it)->getUrl().find(filtro) != std::string::npos) {
            posicionActual = it;
            coincidenciaEncontrada = true;
            break; 
        }
    }

    if (!coincidenciaEncontrada) {
        posicionActual = historial.end(); 
    }
}

Historial* Historial::cargarArchivoHistorial(std::ifstream& in) {
    Historial* historial = new Historial();

    size_t numSitios;
    in.read(reinterpret_cast<char*>(&numSitios), sizeof(numSitios));

    // Cargar cada sitio web
    for (size_t i = 0; i < numSitios; ++i) {
        SitioWeb* sitio = SitioWeb::cargarArchivoSitioWeb(in); // Asumiendo que hay un método para cargar SitioWeb
        historial->historial.push_back(sitio);
    }

    // Cargar la posición relativa
    int posicionActualIdx;
    in.read(reinterpret_cast<char*>(&posicionActualIdx), sizeof(posicionActualIdx));

    // Reconstruir el iterador
    historial->posicionActual = std::next(historial->historial.begin(), posicionActualIdx);

    return historial;
}
void Historial::guardarArchivoHistorial(std::ofstream& out) {
    // Calcular la posición relativa del iterador
    int posicionActualIdx = std::distance(historial.begin(), posicionActual);

    // Guardar el número de sitios web en el historial
    size_t numSitios = historial.size();
    out.write(reinterpret_cast<const char*>(&numSitios), sizeof(numSitios));

    // Guardar cada sitio web
    for (const auto& sitio : historial) {
        sitio->guardarArchivoSitioWeb(out); // Asumiendo que hay un método para guardar SitioWeb
    }

    // Guardar la posición relativa
    out.write(reinterpret_cast<const char*>(&posicionActualIdx), sizeof(posicionActualIdx));
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





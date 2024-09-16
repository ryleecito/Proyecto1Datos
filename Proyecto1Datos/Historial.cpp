#include "Historial.h"
#include <sstream>

Historial::Historial() : posicionActual(historial.end()) {}

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
    if (posicionActual != historial.begin()) {
        --posicionActual;
    }
}

void Historial::avanzar() {
    if (posicionActual != std::prev(historial.end())) {
        ++posicionActual;
    }
}

void Historial::limpiarHistorial() {
    for (SitioWeb* sitio : historial) {
        delete sitio;
    }
    historial.clear();
    posicionActual = historial.end();
}

void Historial::importarHistorial(std::ifstream& in) {
    limpiarHistorial();

    std::string url, titulo, dominio;
    while (std::getline(in, url)) {
        if (std::getline(in, titulo) && std::getline(in, dominio)) {
            SitioWeb* sitio = new SitioWeb(url, titulo, dominio);
            add(sitio);
        }
    }
}

void Historial::exportarHistorial(std::ofstream& out) {

    //for (const SitioWeb* sitio : historial) {
    //    out << *sitio->getUrl() << '\n';
    //    out << sitio->getTitulo() << '\n';
    //    out << sitio->getDominio() << '\n';

    //}
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
    // Mientras el tamaño del historial sea mayor que el límite configurado
    while (historial.size() > configuraciones->getMaxEntradas()) {
        // Eliminar la primera entrada (la más antigua)
        delete historial.front();  // Liberar la memoria si es necesario
        historial.pop_front();     // Eliminar del historial
    }

    // Después de eliminar, actualizar la posición actual si es necesario
    if (posicionActual == historial.end()) {
        posicionActual = --historial.end();
    }
}

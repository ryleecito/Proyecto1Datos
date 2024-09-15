#include "Historial.h"
#include <sstream>

Historial::Historial() : posicionActual(historial.end()) {}

Historial::~Historial() {
    for (auto sitio : historial) {
        delete sitio;
    }
}

void Historial::add(SitioWeb* sitioWeb) {
    if (sitioWeb == nullptr) {
        return;
    }

    if (posicionActual != historial.end()) {
        // Elimina todos los elementos futuros después del sitio actual
        historial.erase(std::next(posicionActual), historial.end());
    }

    // Agrega el nuevo sitio al final del historial
    historial.push_back(sitioWeb);

    // Actualiza el iterador al nuevo sitio web agregado
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
    for (auto sitio : historial) {
        delete sitio;
    }
    historial.clear();
    posicionActual = historial.end();
}

void Historial::importarHistorial(std::ifstream& in) {
    limpiarHistorial();

    std::string url, titulo, dominio;
    while (getline(in, url)) {
        if (getline(in, titulo) && getline(in, dominio)) {
            SitioWeb* sitio = new SitioWeb(url, titulo, dominio);
            add(sitio);
        }
    }
}

void Historial::exportarHistorial(std::ofstream& out) {
    for (auto sitio : historial) {
        out << sitio->getUrl() << std::endl;
        out << sitio->getTitulo() << std::endl;
        out << sitio->getDominio() << std::endl;
    }
}

std::list<SitioWeb*> Historial::getHistorial() {
    return historial;
}

SitioWeb* Historial::getSitioActual() {
    if (posicionActual != historial.end()) {
        return *posicionActual;
    }
    return nullptr;
}

string Historial::toString() const {

    stringstream ss;
    ss << "Historial:\n";

    for (auto sitio : historial) {
        ss << sitio->toString() << "\n";
    }

    return ss.str();
}
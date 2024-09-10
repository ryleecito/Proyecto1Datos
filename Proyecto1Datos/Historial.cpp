#include "Historial.h"

Historial::Historial() : posicionActual(historial.end()) {}

Historial::~Historial() {
    for (auto sitio : historial) {
        delete sitio;  
    }
}

void Historial::navegar(SitioWeb* sitioWeb) {
    
    if (posicionActual != historial.end()) {
        auto it = next(posicionActual);
        historial.erase(it, historial.end());
    }
    historial.push_back(sitioWeb);
    posicionActual = prev(historial.end());
}

void Historial::retroceder() {
    if (posicionActual != historial.begin()) {
        --posicionActual;
    }
}

void Historial::avanzar() {
    if (posicionActual != prev(historial.end())) {
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

void Historial::importarHistorial(ifstream& in) {
    limpiarHistorial();

    std::string url, titulo, dominio;
    while (getline(in, url)) {
        if (getline(in, titulo) && getline(in, dominio)) {
            SitioWeb* sitio = new SitioWeb(url, titulo, dominio);
            navegar(sitio);
        }
    }
}

void Historial::exportarHistorial(ofstream& out) {
    for (auto sitio : historial) {
        out << sitio->getUrl() << endl;
        out << sitio->getTitulo() << endl;
        out << sitio->getDominio() << endl;
    }
}

list<SitioWeb*> Historial::getHistorial() {
    return historial;
}

SitioWeb* Historial::getSitioActual() {
    if (posicionActual != historial.end()) {
        return *posicionActual;
    }
    return nullptr;
}
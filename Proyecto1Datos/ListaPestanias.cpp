#include "ListPestanias.h"

ListPestanias::ListPestanias()
    : posicionActual(pestanias.end()), posicionActualIdx(-1) {}

ListPestanias::~ListPestanias() {
    limpiarPestanias();
}

int ListPestanias::size() const {
    return (int)pestanias.size();
}

void ListPestanias::add(Pestania* pestania) {
    pestanias.push_back(pestania);
    posicionActual = std::prev(pestanias.end());  
    posicionActualIdx = (int)pestanias.size() - 1;
}

void ListPestanias::retroceder() {
    if (posicionActual != pestanias.begin()) {
        --posicionActual;
        --posicionActualIdx;  
    }
}

void ListPestanias::avanzar() {
    if (posicionActual != std::prev(pestanias.end())) {
        ++posicionActual;
        ++posicionActualIdx;
    }
}

void ListPestanias::limpiarPestanias() {
    for (auto& pestania : pestanias) {
        delete pestania;  
    }
    pestanias.clear();   
    posicionActual = pestanias.end();
    posicionActualIdx = -1;  
}

int ListPestanias::getPosicionActualIndex() const {
    return posicionActualIdx; 
}

std::string ListPestanias::toString() const {
    std::stringstream s;
    for (const auto& pestania : pestanias) {
        s << pestania->toString() << std::endl;
    }
    return s.str();
}

std::list<Pestania*> ListPestanias::getPestanias() const {
    return pestanias;
}

Pestania* ListPestanias::getPestaniaActual() const {
    if (posicionActual != pestanias.end()) {
        return *posicionActual;
    }
    return nullptr;
}

void ListPestanias::agregarPaginaWeb(SitioWeb* sitio) {
    if (posicionActual != pestanias.end()) {
        (*posicionActual)->agregarPaginaWeb(sitio);
    }
}

void ListPestanias::importarPestanias(std::ifstream& in) {
    limpiarPestanias();
    std::string nombre;
    while (std::getline(in, nombre)) {
        // Implementar la lógica para agregar pestañas desde un archivo
    }
}

void ListPestanias::exportarPestanias(std::ofstream& out) {
    for (const auto& pestania : pestanias) {
        // Implementar la lógica para exportar pestañas a un archivo
    }
}
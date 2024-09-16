#include "ListPestanias.h"


ListPestanias::ListPestanias() : posicionActual(pestanias.end()) {}

ListPestanias::~ListPestanias() {
    for (auto pestania : pestanias) {
        delete pestania;
    }
}

int ListPestanias::size() {
    return pestanias.size();
}

void ListPestanias::add(Pestania* pestania) {
    if (posicionActual != pestanias.end()) {
        auto it = std::next(posicionActual);  
        pestanias.erase(it, pestanias.end());
    }
    pestanias.push_back(pestania);
    posicionActual = std::prev(pestanias.end()); 
}

void ListPestanias::retroceder() {
    if (posicionActual != pestanias.begin()) {
        --posicionActual;
    }
}

void ListPestanias::avanzar() {
    if (posicionActual != std::prev(pestanias.end())) {
        ++posicionActual;
    }
}

void ListPestanias::limpiarPestanias() {
    // Iteramos por todas las pestañas y las borramos
    for (auto it = pestanias.begin(); it != pestanias.end(); ++it) {
        delete* it; // Liberamos la memoria de la pestaña
    }
    // Limpiamos la lista de pestañas
    pestanias.clear();
    // Reiniciamos posicionActual
    posicionActual = pestanias.end();

}

void ListPestanias::importarPestanias(std::ifstream& in) {
    limpiarPestanias();

    std::string nombre;
    while (std::getline(in, nombre)) {
       
    }
}

void ListPestanias::exportarPestanias(std::ofstream& out) {
    for (auto pestania : pestanias) {
      
    }
}

int ListPestanias::posicionActualIndex() {
    if (pestanias.empty()) {
        return -1;
    }
    return std::distance(pestanias.begin(), posicionActual);
}

std::string ListPestanias::toString() {
    std::stringstream s;
    for (auto pestania : pestanias) {
        s << pestania->toString() << std::endl;
    }
    return s.str();
}

std::list<Pestania*> ListPestanias::getPestanias() {
    return pestanias;
}

void ListPestanias::agregarPaginaWeb(SitioWeb* sitio) {
    if (posicionActual != pestanias.end()) {
        (*posicionActual)->agregarPaginaWeb(sitio);
    }
}

Pestania* ListPestanias::getPestaniaActual() {
    if (posicionActual != pestanias.end()) {
        return *posicionActual;
    }
    return nullptr;
}

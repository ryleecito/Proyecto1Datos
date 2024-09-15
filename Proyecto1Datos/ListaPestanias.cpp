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
        auto it = std::next(posicionActual);  // Usa std::next en lugar de next para evitar ambigüedad
        pestanias.erase(it, pestanias.end());
    }
    pestanias.push_back(pestania);
    posicionActual = std::prev(pestanias.end()); // Usa std::prev en lugar de prev
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
    for (auto pestania : pestanias) {
        delete pestania;
    }
    pestanias.clear();
    posicionActual = pestanias.end();
}

void ListPestanias::importarPestanias(std::ifstream& in) {
    limpiarPestanias();

    std::string nombre;
    while (std::getline(in, nombre)) {
        // Completar la lógica para crear nuevas pestañas
        // Ejemplo (si tienes constructor adecuado):
        // Pestania* pestania = new Pestania(nombre);
        // pestanias.push_back(pestania);
    }
}

void ListPestanias::exportarPestanias(std::ofstream& out) {
    for (auto pestania : pestanias) {
        // Completar la lógica para exportar cada pestaña
        // Ejemplo (si tienes método adecuado en Pestania):
        // out << pestania->getNombre() << std::endl;
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
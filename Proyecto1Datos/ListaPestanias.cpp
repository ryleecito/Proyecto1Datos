#include "ListPestanias.h"

ListPestanias::ListPestanias() : posicionActual(historial.end()) {}

ListPestanias::~ListPestanias() {
    for (auto pestania : historial) {
        delete pestania;
    }
}

void ListPestanias::navegar(Pestania* pestania) {
    if (posicionActual != historial.end()) {
        auto it = next(posicionActual);
        historial.erase(it, historial.end());
    }
    historial.push_back(pestania);
    posicionActual = std::prev(historial.end());
}

void ListPestanias::retroceder() {
    if (posicionActual != historial.begin()) {
        --posicionActual;
    }
}

void ListPestanias::avanzar() {
    if (posicionActual != prev(historial.end())) {
        ++posicionActual;
    }
}

void ListPestanias::limpiarHistorial() {
    for (auto pestania : historial) {
        delete pestania;
    }
    historial.clear();
    posicionActual = historial.end();
}

void ListPestanias::importarHistorial(ifstream& in) {
    limpiarHistorial();

    string nombre; 
    while (getline(in, nombre)) {
       /* Pestania* pestania = new Pestania(nombre);*/ 
     /*   navegar(pestania);*/
    }
}

void ListPestanias::exportarHistorial(ofstream& out) {
    for (auto pestania : historial) {
      /*  out << pestania->getNombre() << std::endl*/; 
    }
}

string ListPestanias::toString()
{
    std::stringstream s;
    for (auto pestania : historial) {
        s << pestania->toString() << endl;
    }
    return s.str();
}

list<Pestania*> ListPestanias::getHistorial() {
    return historial;
}

Pestania* ListPestanias::getPestaniaActual() {
    if (posicionActual != historial.end()) {
        return *posicionActual;
    }
    return nullptr;
}
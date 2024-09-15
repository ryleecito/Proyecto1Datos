#include "ListPestanias.h"

ListPestanias::ListPestanias() : posicionActual(pestanias.end()) {}

ListPestanias::~ListPestanias() {
    for (auto pestania : pestanias) {
        delete pestania;
    }
}

int ListPestanias::size()
{
    return pestanias.size();
}

void ListPestanias::add(Pestania* pestania) {
    if (posicionActual != pestanias.end()) {
        auto it = next(posicionActual);
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
    if (posicionActual != prev(pestanias.end())) {
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

void ListPestanias::importarPestanias(ifstream& in) {
    limpiarPestanias();

    string nombre; 
    while (getline(in, nombre)) {
       /* Pestania* pestania = new Pestania(nombre);*/ 
     /*   navegar(pestania);*/
    }
}

void ListPestanias::exportarPestanias(ofstream& out) {
    for (auto pestania : pestanias) {
      /*  out << pestania->getNombre() << std::endl*/; 
    }
}

int ListPestanias::posicionActualIndex()
{
    // Verifica si la lista de pestañas no está vacía y si la posición actual es válida
    if (pestanias.empty()) {
        return -1; // Si la lista está vacía, retornamos -1 o cualquier otro valor que indique error
    }

    // Calcula la distancia entre el inicio de la lista y la posición actual
    return std::distance(pestanias.begin(), posicionActual);
}


string ListPestanias::toString()
{
    std::stringstream s;
    for (auto pestania : pestanias) {
        s << pestania->toString() << endl;
    }
    return s.str();
}

list<Pestania*> ListPestanias::getPestanias() {
    return pestanias;
}

Pestania* ListPestanias::getPestaniaActual() {
    if (posicionActual != pestanias.end()) {
        return *posicionActual;
    }
    return nullptr;
}
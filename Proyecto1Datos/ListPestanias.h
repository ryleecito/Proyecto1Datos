#pragma once
#include "Pestania.h"

class ListPestanias
{
private:

    list<Pestania*> pestanias;
    list<Pestania*>::iterator posicionActual;

public:
    ListPestanias();
    virtual ~ListPestanias();
    int size();
    void add(Pestania* pestania);
    void retroceder();
    void avanzar();
    void limpiarPestanias();
    void importarPestanias(ifstream& in);
    void exportarPestanias(ofstream& out);
    int posicionActualIndex();
	string toString();
    list<Pestania*> getPestanias();
    Pestania* getPestaniaActual();
};

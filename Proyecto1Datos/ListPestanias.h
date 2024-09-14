#pragma once
#include "Pestania.h"

class ListPestanias
{
private:

    list<Pestania*> historial;
    list<Pestania*>::iterator posicionActual;

public:
    ListPestanias();
    virtual ~ListPestanias();
    void navegar(Pestania* pestania);
    void retroceder();
    void avanzar();
    void limpiarHistorial();
    void importarHistorial(ifstream& in);
    void exportarHistorial(ofstream& out);
	string toString();
    list<Pestania*> getHistorial();
    Pestania* getPestaniaActual();
};

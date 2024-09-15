#pragma once
#include <list>
#include "AdminHistorial.h"
#include "SitioWeb.h"
#include <fstream>

class Historial
{
private:
    list<SitioWeb*> historial;
    list<SitioWeb*>::iterator posicionActual;

public:
    Historial();
    virtual ~Historial();
    void add(SitioWeb* sitioWeb);
    void retroceder();
    void avanzar();
    void limpiarHistorial();
    void importarHistorial(ifstream& in);
    void exportarHistorial(ofstream& out);
    list<SitioWeb*> getHistorial();
    SitioWeb* getSitioActual();
    string toString() const;

};
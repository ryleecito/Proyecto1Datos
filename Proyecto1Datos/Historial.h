#pragma once
#include <deque>
#include <list>
#include <fstream>
#include <string>
#include "AdminHistorial.h"
#include "SitioWeb.h"

class Historial
{
private:
    std::deque<SitioWeb*> historial;
    std::deque<SitioWeb*>::iterator posicionActual;

public:
    Historial();
    virtual ~Historial();

    int size() const;
    void add(SitioWeb* sitioWeb);
    void retroceder();
    void avanzar();
    void limpiarHistorial();
    void importarHistorial(std::ifstream& in);
    void exportarHistorial(std::ofstream& out);
    std::deque<SitioWeb*> getHistorial() const;
    SitioWeb* getSitioActual() const;
    std::string toString() const;
};
#pragma once
#include <list>
#include <fstream>
#include <string>
#include "AdminHistorial.h"
#include "SitioWeb.h"

class Historial
{
private:
    std::list<SitioWeb*> historial; 
    std::list<SitioWeb*>::iterator posicionActual; 

public:

    Historial();
    virtual ~Historial();

    int size(); 
    void add(SitioWeb* sitioWeb); 
    void retroceder(); 
    void avanzar(); 
    void limpiarHistorial();
    void importarHistorial(std::ifstream& in); 
    void exportarHistorial(std::ofstream& out); 
    std::list<SitioWeb*> getHistorial(); 
    SitioWeb* getSitioActual(); 
    std::string toString() const; 
};
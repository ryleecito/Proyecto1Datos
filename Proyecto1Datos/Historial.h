#pragma once
#include <list>
#include <fstream>
#include <string>
#include "AdminHistorial.h"
#include "SitioWeb.h"

class Historial
{
private:
    std::list<SitioWeb*> historial; // Calificaci�n de std::list
    std::list<SitioWeb*>::iterator posicionActual; // Calificaci�n de std::list y std::iterator

public:
    // Constructor y Destructor
    Historial();
    virtual ~Historial();

    // M�todos
    int size(); // Retorna el tama�o del historial
    void add(SitioWeb* sitioWeb); // Agrega un sitio al historial
    void retroceder(); // Retrocede en el historial
    void avanzar(); // Avanza en el historial
    void limpiarHistorial(); // Limpia el historial
    void importarHistorial(std::ifstream& in); // Importa historial desde un archivo
    void exportarHistorial(std::ofstream& out); // Exporta historial a un archivo
    std::list<SitioWeb*> getHistorial(); // Retorna el historial
    SitioWeb* getSitioActual(); // Retorna el sitio actual
    std::string toString() const; // Representaci�n textual del historial
};
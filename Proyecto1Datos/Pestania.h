#pragma once
#include <iostream>
#include <sstream>
#include <list>
#include <fstream>  // Para std::ifstream y std::ofstream
#include <string>   // Para std::string
#include "Marcador.h"
#include "SitioWeb.h"
#include "Historial.h"

class Pestania
{
private:
    Historial* historial; // Puntero al historial

public:
    // Constructores y Destructor
    Pestania();
    Pestania(Historial* historial);
    virtual ~Pestania();

    // Métodos
    void irAtras();
    void irAdelante();
    void setHistorial(Historial* historial);
    Historial* getHistorial() const; // Añadir const para indicar que no modifica el objeto
    bool operator==(const Pestania& other) const; // Constante ya que solo compara
    void importarHistorial(std::ifstream& input); // Calificar std::ifstream
    void exportarHistorial(std::ofstream& output); // Calificar std::ofstream
    void agregarPaginaWeb(SitioWeb* sitio);
    std::string toString() const; // Calificar std::string
};


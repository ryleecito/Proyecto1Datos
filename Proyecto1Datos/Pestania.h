#pragma once
#include <iostream>
#include <sstream>
#include <deque>
#include <fstream>  
#include <string>   
#include "Marcador.h"
#include "SitioWeb.h"
#include "Historial.h"

class Pestania
{
private:

    Historial* historial; 

public:
  
    Pestania();
    Pestania(Historial* historial);
    virtual ~Pestania();

 
    void irAtras();
    void irAdelante();
    void setHistorial(Historial* historial);
    Historial* getHistorial() const; 
    bool operator==(const Pestania& other) const;
    void agregarPaginaWeb(SitioWeb* sitio);
    std::string toString() const; 

	void guardarArchivoPestania(std::ofstream& out);
	static Pestania* cargarArchivoPestania(std::ifstream& in);
};


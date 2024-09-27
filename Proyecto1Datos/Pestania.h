#pragma once
#include <iostream>
#include <sstream>
#include <deque>
#include <fstream>  
#include <string>   
#include <chrono>
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
    void setHistorial(Historial* historial);
    Historial* getHistorial() const; 
    //bool operator==(const Pestania& other) const;

    std::string toString() const; 

	void guardarArchivoPestania(std::ofstream& out);
	static Pestania* cargarArchivoPestania(std::ifstream& in);


    //Metodos de historial

    int sizeHistorial() const;
    void agregarPaginaWeb(SitioWeb* sitio);
    void irAtras();
    void irAdelante();
    std::list<SitioWeb*> filtrarPaginasPorNombre(const std::string& nombre) const;
    SitioWeb* getSitioActual() const;
    void ajustarTamanoHistorial();
	bool limpiarEntradasViejas();
  

    //Metodos de SitioWeb

    std::string getUrlActual() const;
    std::string getTituloActual() const;
    std::string getDominioActual() const;
};


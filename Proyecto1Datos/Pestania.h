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
    Pestania(const Pestania&);
    virtual ~Pestania();
    void setHistorial(Historial* historial);
    Historial* getHistorial() const; 

    std::string toString() const; 

	void guardarArchivoPestania(std::ofstream& out);
	static Pestania* cargarArchivoPestania(std::ifstream& in);


    //Metodos de historial

    int sizeHistorial() const;
    void agregarPaginaWeb(SitioWeb* sitio);
    void irAtras();
    void irAdelante();
    SitioWeb* getSitioActual() const;
    void ajustarTamanoHistorial();
	bool limpiarEntradasViejas();
    std::string busquedaPalabraClave(const std::string& palabraClave);
	void moverseAPrimeraCoincidencia();
    void setFiltro(const std::string& filtro);
  

    //Metodos de SitioWeb

    std::string getUrlActual() const;
    std::string getTituloActual() const;
    std::string getDominioActual() const;
};


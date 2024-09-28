#pragma once
#include <list>
#include <string>
#include <fstream>
#include "SitioWeb.h"

class Marcador
{
private:
    SitioWeb* sitio;
    std::list<std::string*> etiquetas;

public:
    Marcador();
    Marcador(SitioWeb* sitio, const std::list<std::string*>& etiquetas);
	Marcador(SitioWeb* sitio, const std::string& etiqueta);
    virtual ~Marcador();

	void anadirEtiqueta(const std::string& etiqueta);

    SitioWeb* getSitio() const;
    std::string toString() const;

    void guardarArchivoMarcador(std::ofstream& out);
    static Marcador* cargarArchivoMarcador(std::ifstream& in);

    const std::list<std::string*>& getEtiquetas() const; 
    void setEtiquetas(const std::list<std::string*>& nuevasEtiquetas); 

    
};
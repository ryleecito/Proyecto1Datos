#pragma once
#include <list>
#include <string>
#include "SitioWeb.h"

class Marcador
{
private:
    SitioWeb* sitio;
    std::string etiqueta;

public:
    Marcador();
    Marcador(SitioWeb* sitio, const std::string);
    virtual ~Marcador();


    SitioWeb* getSitio() const;
    std::string toString() const;

	void guardarArchivoMarcador(std::ofstream& out);
	static Marcador* cargarArchivoMarcador(std::ifstream& in);

};

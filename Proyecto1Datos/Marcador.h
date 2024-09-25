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
    // Constructores y Destructor
    Marcador();
    Marcador(SitioWeb* sitio, const std::string);
    virtual ~Marcador();

    // Métodos
    void agregarEtiqueta(const std::string& etiqueta);
    void eliminarEtiqueta(const std::string& etiqueta);
    SitioWeb* getSitio() const;
    std::string toString() const;

	void guardarArchivoMarcador(std::ofstream& out);
	static Marcador* cargarArchivoMarcador(std::ifstream& in);

};

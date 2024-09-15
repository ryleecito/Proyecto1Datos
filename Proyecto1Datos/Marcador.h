#pragma once
#include <list>
#include <string>
#include "SitioWeb.h"

class Marcador
{
private:
    SitioWeb* sitio;
    std::list<std::string> listaEtiquetas;

public:
    // Constructores y Destructor
    Marcador();
    Marcador(SitioWeb* sitio, const std::list<std::string>& listaEtiquetas);
    virtual ~Marcador();

    // Métodos
    void agregarEtiqueta(const std::string& etiqueta);
    void eliminarEtiqueta(const std::string& etiqueta);
    SitioWeb* getSitio() const;

};

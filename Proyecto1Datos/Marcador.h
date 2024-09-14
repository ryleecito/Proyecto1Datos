#pragma once
#include "SitioWeb.h"
#include <list>
class Marcador
{
private:

	SitioWeb* sitio;
	list<string> listaEtiquetas;

public:
	Marcador();
	Marcador(SitioWeb sitio, list<string> listaEtiquetas);
	virtual ~Marcador();
	void agregarEtiqueta(string etiqueta);
	void eliminarEtiqueta(string etiqueta);
	SitioWeb* getSitio();

};


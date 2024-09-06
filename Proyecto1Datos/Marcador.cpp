#include "Marcador.h"

Marcador::Marcador()
{
	this->sitio = nullptr;

}

Marcador::Marcador(SitioWeb sitio, list<string> listaEtiquetas)
{
	this->sitio = &sitio;
	this->listaEtiquetas = listaEtiquetas;

}

Marcador::~Marcador()
{
	
}

void Marcador::agregarEtiqueta(string etiqueta)
{
	listaEtiquetas.push_back(etiqueta);
}

void Marcador::eliminarEtiqueta(string etiqueta)
{
	listaEtiquetas.remove(etiqueta);
}

SitioWeb* Marcador::getSitio()
{
	return sitio;
}

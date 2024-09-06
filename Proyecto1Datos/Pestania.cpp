#include "Pestania.h"

Pestania::Pestania()
{
	sitioWebActual = NULL;
	historial = NULL;
}

Pestania::Pestania(SitioWeb* sitioWebActual, Historial* historial)
{
	this->sitioWebActual = sitioWebActual;
	this->historial = historial;
}

Pestania::~Pestania()
{
	if (sitioWebActual != NULL)
	{
		delete sitioWebActual;
	}
	if (historial != NULL)
	{
		delete historial;
	}
}

void Pestania::irAtras()
{
}

void Pestania::irAdelante()
{
}

void Pestania::agregarMarcador(SitioWeb* sitioWeb)
{
}

list<Marcador> Pestania::getListaMarcadores(string x)
{
	return list<Marcador>();
}

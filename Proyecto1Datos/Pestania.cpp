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

void Pestania::setSitioWebActual(SitioWeb* sitioWebActual1)
{
	if (this->sitioWebActual != NULL)
	{
		delete this->sitioWebActual;
	}
	this->sitioWebActual = sitioWebActual1;
}

SitioWeb* Pestania::getSitioWebActual()
{
	return sitioWebActual;
}

void Pestania::setHistorial(Historial* historial1)
{
	if (this->historial != NULL)
	{
		delete this->historial;
	}
	this->historial = historial1;
}

Historial* Pestania::getHistorial()
{
	return historial;
}

void Pestania::importarHistorial(ifstream& input) {
	if (historial) {  
		historial->importarHistorial(input);
	}
}

void Pestania::exportarHistorial(ofstream& output) {
	if (historial) {
		historial->exportarHistorial(output);
	}
}
bool Pestania::operator==(const Pestania& other) const {
	
	return sitioWebActual == other.sitioWebActual;

}
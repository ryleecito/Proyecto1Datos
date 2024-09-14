#pragma once
#include <iostream>
#include <sstream>
#include <list>
#include "Marcador.h"
#include "SitioWeb.h"
#include "Historial.h"
using namespace std;

class Pestania
{
private:

	SitioWeb* sitioWebActual;
	Historial* historial;

public:
	Pestania();
	Pestania(SitioWeb* sitioWebActual, Historial* historial);
	virtual ~Pestania();
	void irAtras();	
	void irAdelante();
	void setSitioWebActual(SitioWeb* sitioWebActual1);
	SitioWeb* getSitioWebActual();
	void setHistorial(Historial* historial);
	Historial* getHistorial();
	bool operator==(const Pestania& other) const;
	void importarHistorial(ifstream& input);
	void exportarHistorial(ofstream& output);
	string toString();

	
};


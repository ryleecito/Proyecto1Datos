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
	list<Marcador> listaMarcadores;
	SitioWeb* sitioWebActual;
	Historial* historial;
public:
	Pestania();
	Pestania(SitioWeb* sitioWebActual, Historial* historial);
	virtual ~Pestania();
	void irAtras();	
	void irAdelante();
	void agregarMarcador(SitioWeb* sitioWeb);
	list<Marcador> getListaMarcadores(string x);
	
};


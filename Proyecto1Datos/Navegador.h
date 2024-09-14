#pragma once
#include "Pestania.h"
#include "Sesion.h"
#include <fstream>
class Navegador
{
private:
	list<Pestania*> listaPestanias;
	list<Marcador*> marcadoresGuardados;
	Pestania* pestaniaActual;
	//Sesion* sesionActual;
	bool modoIncognito;


public:

	Navegador();
	virtual ~Navegador();
	void nuevaPestania(Pestania* pest);
	void cerrarPestania(Pestania* pest); 
	void cambiarmodoIncognito();
	void importarHistorial(const string& nombreHistorial);
	void exportarHistorial(const string& nombreHistorial);
	//Sesion* getSesion();
	//void setSesion(Sesion* sesion);
	string toString();
	list<Pestania*> getListaPestanias();
	list<Marcador*> getMarcadoresGuardados();

	//Metodos de la lista de pestanias
	int cantPestanias();
	Pestania* firstPestania();

	

};


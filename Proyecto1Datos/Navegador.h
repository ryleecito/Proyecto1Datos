#pragma once
#include "Pestania.h"
#include "Sesion.h"
#include "ListPestanias.h"
#include <fstream>
class Navegador
{
private:
	ListPestanias* listaPestanias;
	list<Marcador*> marcadoresGuardados;
	Pestania* pestaniaActual;
	//Sesion* sesionActual;
	bool modoIncognito;


public:

	Navegador();
	virtual ~Navegador();
	void cambiarmodoIncognito();
	/*void importarHistorial(const string& nombreHistorial);
	void exportarHistorial(const string& nombreHistorial);*/
	//Sesion* getSesion();
	//void setSesion(Sesion* sesion);
	string toString();
	ListPestanias* getListaPestanias();
	list<Marcador*> getMarcadoresGuardados();
	

	

};


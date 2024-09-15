#pragma once
#include "Pestania.h"
#include "Sesion.h"
#include "ListPestanias.h"
#include <fstream>
class Navegador
{
private:

	ListPestanias* listaPestanias;
	list<SitioWeb*> sitios;
	list<Marcador*> marcadoresGuardados;
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
	
	//metodos de lista pestanias
	int cantidadPestanias();
	void agregarPestania(Pestania* pest);
	int posicionDelIndex();
	void pestaniaAnterior();
	void pestaniaSiguiente();
	void agregarPaginaWeb(SitioWeb* sitio);
	string mostrarPestaniaActual();
	

	// metodos sitios web
	SitioWeb* buscarPaginaWeb(const string url);

	



	

};


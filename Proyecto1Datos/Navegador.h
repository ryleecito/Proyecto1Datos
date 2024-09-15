#pragma once
#include "Pestania.h"
#include "Sesion.h"
#include "ListPestanias.h"
#include <fstream>
class Navegador
{
private:

	ListPestanias* listaPestanias;
	std::list<SitioWeb*> sitios;
	std::list<Marcador*> marcadoresGuardados;
	std::list<Marcador*>::iterator posicionActual;
	bool modoIncognito;


public:

	Navegador();
	virtual ~Navegador();
	void cambiarmodoIncognito();
	/*void importarHistorial(const string& nombreHistorial);
	void exportarHistorial(const string& nombreHistorial);*/
	//Sesion* getSesion();
	//void setSesion(Sesion* sesion);
	std::string toString();
	ListPestanias* getListaPestanias();
	std::list<Marcador*> getMarcadoresGuardados();
	
	//metodos de lista pestanias
	int cantidadPestanias();
	void agregarPestania(Pestania* pest);
	int posicionDelIndex();
	void pestaniaAnterior();
	void pestaniaSiguiente();
	void agregarPaginaWeb(SitioWeb* sitio);
	std::string mostrarPestaniaActual();

	//bookmarks
	void agregarMarcador(Marcador* );
	std:: string MostrarMarcadoresGuardados() const;
	

	// metodos sitios web
	SitioWeb* getSitioActual();
	SitioWeb* buscarPaginaWeb(const std::string url);
	void paginaAnterior();
	void paginaSiguiente();
	int cantidadPaginas();
	
	



	

};


#pragma once
#include "Pestania.h"
#include "Sesion.h"
#include "ListaPestanias.h"
#include <fstream>
class Navegador
{
private:

	ListPestanias* listaPestanias;
	ListPestanias* listaPestaniasIncognito;
	std::list<SitioWeb*> sitios;
	std::list<Marcador*> marcadoresGuardados;
	bool modoIncognito;


public:

	Navegador();
	virtual ~Navegador();
	std::string toString();
	ListPestanias* getListaPestanias();
	std::list<Marcador*> getMarcadoresGuardados();
	ListPestanias* getListaPestaniasIncognito();
	std::list<SitioWeb*>* getListaSitiosW();
	
	// metodos incognito
	void cambiarModoIncognito();
	bool getModoIncognito();
	
	
	//metodos de lista pestanias
	int cantidadPestanias();
	void agregarPestania(Pestania* pest);
	int posicionDelIndex();
	void pestaniaAnterior();
	void pestaniaSiguiente();
	void agregarPaginaWeb(SitioWeb* sitio);
	std::string mostrarPestaniaActual();


	//bookmarks
	void agregarMarcador(Marcador*);
	std:: string MostrarMarcadoresGuardados() const;
	

	// metodos sitios web
	SitioWeb* getSitioActual();
	SitioWeb* buscarPaginaWeb(const std::string url);
	void paginaAnterior();
	void paginaSiguiente();
	int cantidadPaginas();

	// metodos de guardar y cargar archivo
	void guardarArchivoNavegador(std::ofstream& out);
	static Navegador* cargarArchivoNavegador(std::ifstream& in);

	void cargarArchivoSitiosWebCSV(const std::string& rutaArchivo);

	
	



	

};


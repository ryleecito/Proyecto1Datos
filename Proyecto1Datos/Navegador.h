#pragma once
#include "Pestania.h"
#include "ListaPestanias.h"
#include <vector>
#include <fstream>
class Navegador
{
private:

	ListPestanias* listaPestanias;
	ListPestanias* listaPestaniasIncognito;
	std::vector<SitioWeb*> sitios;
	std::list<Marcador*> marcadoresGuardados;
	bool modoIncognito;
	ConfigHistorial* configuracion;

public:

	Navegador();
	virtual ~Navegador();
	std::string toString();
	ListPestanias* getListaPestanias();
	std::list<Marcador*> getMarcadoresGuardados();
	ListPestanias* getListaPestaniasIncognito();
	std::vector<SitioWeb*>* getListaSitiosW();

	// metodos incognito
	void cambiarModoIncognito();
	bool getModoIncognito() const;


	//metodos de lista pestanias
	int cantidadPestanias();
	void agregarPestania(Pestania* pest);
	int posicionDelIndex();
	void pestaniaAnterior();
	void pestaniaSiguiente();
	void agregarPaginaWeb(SitioWeb* sitio);
	Pestania* getPestaniaActual();
	std::string mostrarPestaniaActual();
	bool limpiarViejasEntradas();
	void ajustarTamanoHistorial();


	//bookmarks
	void agregarMarcador(Marcador*);
	std::string mostrarMarcadoresGuardados() const;
	Marcador* buscarMarcadorPorSitio(SitioWeb* sitio);



	// metodos sitios web
	SitioWeb* getSitioActual();
	SitioWeb* buscarPaginaWeb(const std::string url);
	void paginaAnterior();
	void paginaSiguiente();
	int cantidadPaginas();
	std::string busquedaPalabraClave(const std::string& palabraClave);
	void setFiltro(const std::string& filtro);
	void moverseAPrimeraCoincidencia();

	// metodos de guardar y cargar archivo
	void guardarArchivoNavegador(std::ofstream& out);
	static Navegador* cargarArchivoNavegador(std::ifstream& in);

	void cargarArchivoSitiosWebCSV(const std::string& rutaArchivo);



	//Metodos de configuracion
	ConfigHistorial* getConfiguraciones() const;
	void setMaxEntradas(int max);
	void setTiempoMaximo(int time);
	void reiniciarConfiguraciones();


};


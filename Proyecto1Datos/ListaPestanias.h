#pragma once
#include "Pestania.h"
#include "PestaniaIncognito.h"

class ListPestanias
{
private:

    std::list<PestaniaAbstracta*> pestanias;
    std::list<PestaniaAbstracta*>::iterator posicionActual;
    int posicionActualIdx; 
   
public:

public:
    ListPestanias();
    virtual ~ListPestanias();

    int size() const;
    void add(PestaniaAbstracta* pestania);
    void retroceder();
    void avanzar();
    void limpiarPestanias();
    int getPosicionActualIndex() const;
    std::string toString() const;
    std::list<PestaniaAbstracta*> getPestanias() const;


	void guardarArchivoListaPestanias(std::ofstream& out);
    static ListPestanias* cargarArchivoListaPestanias(std::ifstream& in);

    //Metodos Pestania

    Historial* getHistorial() const;
    void agregarPaginaWeb(SitioWeb* sitio);
    PestaniaAbstracta* getPestaniaActual() const;
    std::string mostrarPestaniaActual() const;

    //Metodos de historial

    int sizeHistorial() const;
    void irAtras();
    void irAdelante();
    SitioWeb* getSitioActual() const;
    void ajustarTamanoHistorial();
	bool limpiarEntradasViejas();
	void setFiltro(const std::string& filtro);
	std::string busquedaPalabraClave(const std::string& palabraClave);
	void moverseAPrimeraCoincidencia();




};


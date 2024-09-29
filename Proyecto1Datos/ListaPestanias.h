#pragma once
#include "Pestania.h"

class ListPestanias
{
private:

    std::list<Pestania*> pestanias;
    std::list<Pestania*>::iterator posicionActual;
    int posicionActualIdx; 
   
public:

public:
    ListPestanias();
    virtual ~ListPestanias();

    int size() const;
    void add(Pestania* pestania);
    void retroceder();
    void avanzar();
    void limpiarPestanias();
    void reiniciar();
    int getPosicionActualIndex() const;
    std::string toString() const;
    std::list<Pestania*> getPestanias() const;


	void guardarArchivoListaPestanias(std::ofstream& out);
    static ListPestanias* cargarArchivoListaPestanias(std::ifstream& in);

    //Metodos Pestania

    Historial* getHistorial() const;
    void agregarPaginaWeb(SitioWeb* sitio);
    Pestania* getPestaniaActual() const;
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


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
    ConfigHistorial* getConfiguraciones() const;
    void setConfiguraciones(ConfigHistorial* configuraciones);
    std::list<SitioWeb*> filtrarPaginasPorNombre(const std::string& nombre) const;
    SitioWeb* getSitioActual() const;
    void ajustarTamanoHistorial();
	bool limpiarEntradasViejas();
	std::string busquedaPalabraClave(const std::string& palabraClave);




};


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
    Pestania* getPestaniaActual() const;
    void agregarPaginaWeb(SitioWeb* sitio);

	void guardarArchivoListaPestanias(std::ofstream& out);
    static ListPestanias* cargarArchivoListaPestanias(std::ifstream& in);
};


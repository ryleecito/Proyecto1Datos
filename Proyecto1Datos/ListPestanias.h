#pragma once
#include "Pestania.h"

class ListPestanias
{
private:

    std::list<Pestania*> pestanias;
    std::list<Pestania*>::iterator posicionActual;
   
    

public:
    ListPestanias();
    virtual ~ListPestanias();
    int size();
    void add(Pestania* pestania);
    void retroceder();
    void avanzar();
    void limpiarPestanias();
    void importarPestanias(std::ifstream& in);
    void exportarPestanias(std::ofstream& out);
    int posicionActualIndex();
    std::string toString();
    std::list<Pestania*> getPestanias();
	void agregarPaginaWeb(SitioWeb* sitio);
    Pestania* getPestaniaActual();
	
};

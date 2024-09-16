#pragma once
#include "Pestania.h"

class ListPestanias
{
private:

    std::deque<Pestania*> pestanias;
    std::deque<Pestania*>::iterator posicionActual;
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
    std::deque<Pestania*> getPestanias() const;
    Pestania* getPestaniaActual() const;
    void agregarPaginaWeb(SitioWeb* sitio);

    void importarPestanias(std::ifstream& in);
    void exportarPestanias(std::ofstream& out);
};


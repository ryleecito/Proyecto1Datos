#pragma once
#include "PestaniaAbstracta.h"

class Pestania : public PestaniaAbstracta 
{

private:

    Historial* historial;

public:

    Pestania();
    Pestania(Historial* historial);
    Pestania(const Pestania&);
    virtual ~Pestania();
    void setHistorial(Historial* historial);
    Historial* getHistorial() const;

    std::string toString() const;

    void guardarArchivoPestania(std::ofstream& out);
    static Pestania* cargarArchivoPestania(std::ifstream& in);


    //Metodos de historial

    int sizeHistorial() const;
    void agregarPaginaWeb(SitioWeb* sitio);
    void irAtras();
    void irAdelante();
    SitioWeb* getSitioActual() const;
    void ajustarTamanoHistorial();
    bool limpiarSitiosViejos();
    std::string busquedaPalabraClave(const std::string& palabraClave);
    void moverseAPrimeraCoincidencia();
    void setFiltro(const std::string& filtro);


    //Metodos de SitioWeb

    std::string getUrlActual() const;
    std::string getTituloActual() const;
    std::string getDominioActual() const;
};
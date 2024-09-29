#pragma once
#include "Historial.h"


class PestaniaAbstracta {
public:
    virtual ~PestaniaAbstracta() {}

    virtual std::string toString() const = 0;
    virtual Historial* getHistorial() const = 0;

    // Métodos de historial
    virtual int sizeHistorial() const = 0;
    virtual void agregarPaginaWeb(SitioWeb* sitio) = 0;
    virtual void irAtras() = 0;
    virtual void irAdelante() = 0;
    virtual SitioWeb* getSitioActual() const = 0;
    virtual void ajustarTamanoHistorial() = 0;
    virtual bool limpiarEntradasViejas() = 0;
    virtual std::string busquedaPalabraClave(const std::string& palabraClave) = 0;
    virtual void moverseAPrimeraCoincidencia() = 0;
    virtual void setFiltro(const std::string& filtro) = 0;


    // Método para guardar la pestaña en un archivo
    virtual void guardarArchivoPestania(std::ofstream& out) = 0;
};

#pragma once
#include "PestaniaAbstracta.h"

class PestaniaIncognito : public PestaniaAbstracta {
private:

    SitioWeb* sitio;

public:
    PestaniaIncognito();
    PestaniaIncognito(SitioWeb* sitioWeb);
    PestaniaIncognito(const PestaniaIncognito&);
    virtual ~PestaniaIncognito();

    void setSitioWeb(SitioWeb* sitioWeb);
    SitioWeb* getSitioWeb() const;

    Historial* getHistorial() const;

    std::string toString() const;

    // Métodos de historial (pueden ser no aplicables o definidos de otra manera)
    int sizeHistorial() const;
    void agregarPaginaWeb(SitioWeb* sitio);
    void irAtras();
    void irAdelante();
    SitioWeb* getSitioActual() const;
    void ajustarTamanoHistorial();
    bool limpiarEntradasViejas();
    std::string busquedaPalabraClave(const std::string& palabraClave);
    void moverseAPrimeraCoincidencia();
    void setFiltro(const std::string& filtro);



    // Métodos de archivo
    void guardarArchivoPestania(std::ofstream& out);
};
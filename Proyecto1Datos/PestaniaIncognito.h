#pragma once
#include "PestaniaAbstracta.h"

class PestaniaIncognito : public PestaniaAbstracta {
private:

    //Pestania incognito no guarda historial

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

    void guardarArchivoPestania(std::ofstream& out);
};
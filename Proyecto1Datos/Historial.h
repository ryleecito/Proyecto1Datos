#pragma once
#include <deque>
#include <list>
#include <string>
#include "ConfigHistorial.h"
#include "SitioWeb.h"
#include <fstream>
class Historial
{
private:
    std::list<SitioWeb*> historial;
    std::list<SitioWeb*>::iterator posicionActual;
    ConfigHistorial* configuraciones;

public:
    Historial();
    virtual ~Historial();
    int size() const;
    void add(SitioWeb* sitioWeb);
    void retroceder();
    void avanzar();
    void limpiarHistorial();
    ConfigHistorial* getConfiguraciones() const;
    void setConfiguraciones(ConfigHistorial* configuraciones);
    std::list<SitioWeb*> filtrarPaginasPorNombre(const std::string& nombre) const;
    std::list<SitioWeb*> getHistorial() const;
    SitioWeb* getSitioActual() const;
    std::string toString() const;
    void ajustarTamanoHistorial();

    // metodos de guardar y cargar archivo
    void guardarArchivoHistorial(std::ofstream& out);
    static Historial* cargarArchivoHistorial(std::ifstream& in);


};
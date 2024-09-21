#pragma once
#include <deque>
#include <list>
#include <fstream>
#include <string>
#include "ConfigHistorial.h"
#include "SitioWeb.h"

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
    void importarHistorial(std::ifstream& in);
    void exportarHistorial(std::ofstream& out);
	std::list<SitioWeb*> filtrarPaginasPorNombre(const std::string& nombre) const;
    std::list<SitioWeb*> getHistorial() const;
    SitioWeb* getSitioActual() const;
    std::string toString() const;
    void ajustarTamanoHistorial();
};
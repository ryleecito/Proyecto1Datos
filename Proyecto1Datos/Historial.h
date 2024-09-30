#pragma once
#include <list>
#include "SitioWeb.h"

class Historial
{
private:
    std::list<SitioWeb*> historial;
    std::list<SitioWeb*>::iterator posicionActual;
    std::string filtro;
    
public:

    Historial();
    virtual ~Historial();
    int size() const;
    void add(SitioWeb* sitioWeb);
    void eliminarSitioSiExiste(SitioWeb* site);
    void retroceder();
    void avanzar();
    void limpiarHistorial();
    std::string busquedaPalabraClave(const std::string& palabraClave) const;
    std::list<SitioWeb*> getHistorial() const;
    SitioWeb* getSitioActual() const;
    std::string toString() const;
    void ajustarTamanoHistorial();
	bool limpiarSitiosViejos();
    std::string getFiltro();
	void setFiltro(std::string filtro);
    void moverseAPrimeraCoincidencia();

    // metodos de guardar y cargar archivo

	void guardarArchivoHistorial(std::ofstream& in);
	static Historial* cargarArchivoHistorial(std::ifstream& out);

    //Metodos de SitioWeb

    std::string getUrlActual() const;
    std::string getTituloActual() const;
    std::string getDominioActual()const;

};
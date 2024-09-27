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
    std::string filtro;
    
public:
    Historial();
    virtual ~Historial();
    int size() const;
    void add(SitioWeb* sitioWeb);
    void retroceder();
    void avanzar();
    void limpiarHistorial();
    std::list<SitioWeb*> filtrarPaginasPorNombre(const std::string& nombre) const;
    std::list<SitioWeb*> getHistorial() const;
    SitioWeb* getSitioActual() const;
    std::string toString() const;
    void ajustarTamanoHistorial();
	bool limpiarEntradasViejas();

    std::string getFiltro();
	void setFiltro(std::string filtro);


    // metodos de guardar y cargar archivo
    void serializarHistorial(std::ofstream& out);
    static Historial* cargarArchivoHistorial(std::ifstream& in);

    //Metodos de SitioWeb

    std::string getUrlActual() const;
    std::string getTituloActual() const;
    std::string getDominioActual()const;

	bool existeSitioWeb(const std::string url);






};
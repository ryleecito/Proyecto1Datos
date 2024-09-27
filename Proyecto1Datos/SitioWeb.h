#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <chrono>

class SitioWeb
{
private:
    std::string url;
    std::string titulo;
    std::string dominio;
    std::chrono::time_point<std::chrono::system_clock> tiempoDeIngreso;

public:
    SitioWeb();
    SitioWeb(std::string url, std::string titulo, std::string dominio);

    SitioWeb(const SitioWeb& other);
    virtual ~SitioWeb();

    std::string getUrl() const;
    std::string getTitulo() const;
    std::string getDominio() const;
    void setUrl(std::string url);
    void setTitulo(std::string titulo);
    void setDominio(std::string dominio);
    std::string toString() const;
	std::chrono::time_point<std::chrono::system_clock> getTiempoDeIngreso() const;
	void setTiempoDeIngreso(std::chrono::time_point<std::chrono::system_clock> tiempoDeIngreso);

	// metodos de guardar y cargar archivo
	void guardarArchivoSitioWeb(std::ofstream& out);
	static SitioWeb* cargarArchivoSitioWeb(std::ifstream& in);

    // metodos para guardar y cargar con csv 
	void guardarArchivoSitioWebCSV(std::ofstream& out);
	SitioWeb* cargarArchivoSitioWebCSV(std::string &nombre);
    

};


#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

class SitioWeb
{
private:
    std::string url;
    std::string titulo;
    std::string dominio;

public:
    SitioWeb();
    SitioWeb(std::string url, std::string titulo, std::string dominio);

    SitioWeb(const SitioWeb& other);
    virtual ~SitioWeb();

    std::string getUrl();
    std::string getTitulo();
    std::string getDominio();
    void setUrl(std::string url);
    void setTitulo(std::string titulo);
    void setDominio(std::string dominio);
    std::string toString();

	// metodos de guardar y cargar archivo
	void guardarArchivoSitioWeb(std::ofstream& out);
	static SitioWeb* cargarArchivoSitioWeb(std::ifstream& in);

    // metodos para guardar y cargar con csv 
	void guardarArchivoSitioWebCSV(std::ofstream& out);
	SitioWeb* cargarArchivoSitioWebCSV(std::string &nombre);
    

};


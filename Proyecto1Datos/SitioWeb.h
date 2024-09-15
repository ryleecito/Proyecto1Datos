#pragma once
#include <iostream>
#include <sstream>
#include <string>

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
};


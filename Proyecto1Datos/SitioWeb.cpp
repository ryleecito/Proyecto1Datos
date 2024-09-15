#include "SitioWeb.h"

SitioWeb::SitioWeb() : url(""), titulo(""), dominio("") {}

SitioWeb::SitioWeb(std::string url, std::string titulo, std::string dominio)
    : url(url), titulo(titulo), dominio(dominio) {}

SitioWeb::SitioWeb(const SitioWeb& other)
    : url(other.url), titulo(other.titulo), dominio(other.dominio) {}

SitioWeb::~SitioWeb()
{
}

std::string SitioWeb::getUrl()
{
    return url;
}

std::string SitioWeb::getTitulo()
{
    return titulo;
}

std::string SitioWeb::getDominio()
{
    return dominio;
}

void SitioWeb::setUrl(std::string url)
{
    this->url = url;
}

void SitioWeb::setTitulo(std::string titulo)
{
    this->titulo = titulo;
}

void SitioWeb::setDominio(std::string dominio)
{
    this->dominio = dominio;
}

std::string SitioWeb::toString()
{
    std::stringstream s;
    s << "URL: " << url << " Titulo: " << titulo << " Dominio: " << dominio;
    return s.str();
}

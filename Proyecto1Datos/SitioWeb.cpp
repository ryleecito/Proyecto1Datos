#include "SitioWeb.h"

SitioWeb::SitioWeb() : url(""), titulo(""), dominio("") {}

SitioWeb::SitioWeb(string url, string titulo, string dominio): url(url), titulo(titulo), dominio(dominio) {}

SitioWeb::SitioWeb(const SitioWeb& other): url(other.url), titulo(other.titulo), dominio(other.dominio) {}

SitioWeb::~SitioWeb()
{
}

string SitioWeb::getUrl()
{
	return url;
}

string SitioWeb::getTitulo()
{
	return titulo;
}

string SitioWeb::getDominio()
{
	return dominio;
}

void SitioWeb::setUrl(string url)
{
	this->url = url;
}

void SitioWeb::setTitulo(string titulo)
{
	this->titulo = titulo;
}

void SitioWeb::setDominio(string dominio)
{
	this->dominio = dominio;
}

string SitioWeb::toString()
{
	stringstream s;
	s << "URL: " << url << " Titulo: " << titulo << " Dominio: " << dominio;
	return s.str();
}

#pragma once
#include <iostream>
#include <sstream>
using namespace std;
class SitioWeb
{
private:
	string url;
	string titulo;
	string dominio;
public:
	SitioWeb();
	SitioWeb(string url, string titulo, string dominio);
	SitioWeb(const SitioWeb& other); 
	virtual ~SitioWeb();
	string getUrl();
	string getTitulo();
	string getDominio();
	void setUrl(string url);
	void setTitulo(string titulo);
	void setDominio(string dominio);
	string toString();
};


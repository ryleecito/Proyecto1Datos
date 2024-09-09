#pragma once
#include "Pestania.h"
#include <fstream>
class Navegador
{
private:
	list<Pestania> listaPestanias;
	bool modoIncognito;
public:
	Navegador();
	virtual ~Navegador();
	void nuevaPestania(Pestania* pest);
	void cerrarPestania(Pestania* pest); 
	void cambiarmodoIncognito();
	void importarHistorial(const string& nombreHistorial);
	void exportarHistorial(const string& nombreHistorial);

};


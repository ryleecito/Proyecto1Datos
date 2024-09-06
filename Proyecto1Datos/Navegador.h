#pragma once
#include "Pestania.h"
class Navegador
{
private:
	list<Pestania> listaPestanias;
	bool modoIncognito;
public:
	Navegador();
	virtual ~Navegador();
	void nuevaPestania();
	void cerrarPestania();
	void cambiarmodoIncognito();
	void importarHistorial();
	void exportarHistorial();
};


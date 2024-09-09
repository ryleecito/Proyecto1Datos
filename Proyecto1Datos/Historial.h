#pragma once
#include <stack>
#include "AdminHistorial.h"
#include "SitioWeb.h"
#include <fstream>
class Historial
{
private:
	stack<SitioWeb> pilaAtras;
	stack<SitioWeb> pilaAdelante;
public:
	Historial();
	virtual ~Historial();
	void navegar(SitioWeb sitioWeb);
	void retroceder();
	void avanzar();
	void limpiarHistorial();
	void importarHistorial(ifstream& in);
	void exportarHistorial(ofstream& out);
};


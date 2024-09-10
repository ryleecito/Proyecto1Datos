#pragma once
#include <sstream>
#include <iostream>
#include "Historial.h"
#include "SitioWeb.h"
using namespace std;
class Historial;

class AdminHistorial
{
private:
	int maxEntradas;
public:
	AdminHistorial();
	AdminHistorial(int maxEntradas);
	virtual ~AdminHistorial();
	void limpiarEntradasAntiguas(Historial* historial);
	void setMaxEntradas(int maxEntradas);

};


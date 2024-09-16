#pragma once
#include <sstream>
#include <iostream>
#include "Historial.h"
#include "SitioWeb.h"

class ConfigHistorial
{
private:
	int maxEntradas;
public:
	ConfigHistorial();
	ConfigHistorial(int maxEntradas);
	virtual ~ConfigHistorial();
	void setMaxEntradas(int maxEntradas);
	int getMaxEntradas();

};


#pragma once
#include <sstream>
#include <iostream>
#include <fstream>

class ConfigHistorial
{
private:
	int maxEntradas;
public:
	ConfigHistorial();
	ConfigHistorial(const ConfigHistorial&);
	ConfigHistorial(int maxEntradas);
	virtual ~ConfigHistorial();
	void setMaxEntradas(int maxEntradas);
	int getMaxEntradas();

	void guardarArchivoConfigHistorial(std::ofstream& out);
	static ConfigHistorial* cargarArchivoConfigHistorial(std::ifstream& in);

};


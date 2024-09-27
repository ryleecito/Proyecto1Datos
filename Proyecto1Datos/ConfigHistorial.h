#pragma once
#include <sstream>
#include <iostream>
#include <fstream>

class ConfigHistorial
{
private:
	int maxEntradas;
	int tiempoMaximo;
	static ConfigHistorial* instancia;
	ConfigHistorial();
	static void destruirInstancia();

public:
	static ConfigHistorial* getInstancia();
	ConfigHistorial(int maxEntradas,int tiempoMax);
	virtual ~ConfigHistorial();
	void setMaxEntradas(int maxEntradas);
	void setTiempoMaximo(int tiempoMaximo);
	int getTiempoMaximo();
	int getMaxEntradas();

	void guardarArchivoConfigHistorial(std::ofstream& out);
	static ConfigHistorial* cargarArchivoConfigHistorial(std::ifstream& in);
};


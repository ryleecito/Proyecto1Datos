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


public:
	static void destruirInstancia();
	static ConfigHistorial* getInstancia();
	ConfigHistorial(int maxEntradas,int tiempoMax);
	virtual ~ConfigHistorial();
	void setMaxEntradas(int maxEntradas);
	void setTiempoMaximo(int tiempoMaximo);
	int getTiempoMaximo() const;
	int getMaxEntradas() const;

	void guardarArchivoConfigHistorial(std::ofstream& out);
	static ConfigHistorial* cargarArchivoConfigHistorial(std::ifstream& in);
};


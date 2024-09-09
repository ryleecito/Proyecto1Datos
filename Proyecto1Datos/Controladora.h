#pragma once
#include "Navegador.h"
#include "Interfaz.h"
class Controladora
{
private:
	Navegador* navegador;
public:
	Controladora();
	~Controladora();
	void mostrarNavegador();
	void control0(); // Navegador web
	void control1(); // Menu del navegador web
};


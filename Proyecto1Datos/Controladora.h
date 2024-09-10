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
	// menu principal
	void control0(); // Navegador web
	void control1(); // Menu del navegador web
	void control2(); // bookmarks
	void control3(); // historial - importar/exportar
	void control4(); // mostrar bookmarks
	void control5(); // busqueda y filtros
	void control6(); // activar/desactivar modo incognito
	void control7(); // nueva pestaña
	// logica pestañas - paginas
	void control8(); // pagina anterior
	void control9(); // pagina siguiente
	void control10(); // pestaña anterior
	void control11(); // pestaña siguiente

};


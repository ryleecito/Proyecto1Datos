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


	// menu principal

	void control0(); // navegador y menu
	void control1(); // agregar sitio web
	void control2(); // bookmarks
	void control3(); // historial - importar/exportar
	void control4(); // mostrar bookmarks
	void control5(); // busqueda y filtros
	void control6(); // activar/desactivar modo incognito
	void control7(); // nueva pesta�a

	// logica pesta�as - paginas


	void control8(); // pagina anterior
	void control9(); // pagina siguiente
	void control10(); // pesta�a anterior
	void control11(); // pesta�a siguiente

	//funciones de menu navegador

};


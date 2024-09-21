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
	void control8(); //configuracion de historial
	void control9();  // mensaje de salida

	// logica pesta�as - paginas

	void control10(); // pagina anterior
	void control11(); // pagina siguiente
	void control12();// pesta�a anterior
	void control13();// pesta�a siguiente

	//funciones de menu navegador

};


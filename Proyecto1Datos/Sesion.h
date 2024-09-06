#pragma once
#include "Pestania.h"
class Sesion
{
private:
	list<Pestania> listaPestanias;
	list<Marcador> marcadoresGuardados;
public:
	Sesion();
	virtual ~Sesion();
	void guardarSesion();
	void restaurarSesion();
};


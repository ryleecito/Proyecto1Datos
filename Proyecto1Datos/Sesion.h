#pragma once
#include "Pestania.h"

class Sesion
{
private:
	std::list<Pestania> listaPestanias;
	std::list<Marcador> marcadoresGuardados;
public:
	Sesion();
	virtual ~Sesion();
	void guardarSesion();
	void restaurarSesion();
};


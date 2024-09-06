#pragma once
#include <sstream>
#include <iostream>
using namespace std;
class AdminHistorial
{
private:
	int maxEntradas;
public:
	AdminHistorial();
	AdminHistorial(int maxEntradas);
	virtual ~AdminHistorial();
	void limpiarEntradasAntiguas();
	void setMaxEntradas(int maxEntradas);

};


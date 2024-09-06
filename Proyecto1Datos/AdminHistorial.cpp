#include "AdminHistorial.h"

AdminHistorial::AdminHistorial()
{
	maxEntradas = 0;
}

AdminHistorial::AdminHistorial(int maxEntradas)
{
	this->maxEntradas = maxEntradas;
}

AdminHistorial::~AdminHistorial()
{
}

void AdminHistorial::limpiarEntradasAntiguas()
{

}

void AdminHistorial::setMaxEntradas(int maxEntradas)
{
	this->maxEntradas = maxEntradas;
}

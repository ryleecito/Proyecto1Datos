#include "Pestania.h"

Pestania::Pestania()
{
	sitioWebActual = NULL;
	historial = NULL;
}

Pestania::Pestania(SitioWeb* sitioWebActual, Historial* historial)
{
	this->sitioWebActual = sitioWebActual;
	this->historial = historial;
}

Pestania::~Pestania()
{
	if (sitioWebActual != NULL)
	{
		delete sitioWebActual;
	}
	if (historial != NULL)
	{
		delete historial;
	}
}

void Pestania::irAtras()
{
	historial->retroceder();
}

void Pestania::irAdelante()
{
	historial->avanzar();
}


void Pestania::setSitioWebActual(SitioWeb* sitioWebActual1)
{
	if (this->sitioWebActual != NULL)
	{
		delete this->sitioWebActual;
	}
	this->sitioWebActual = sitioWebActual1;
}

SitioWeb* Pestania::getSitioWebActual()
{
	return sitioWebActual;
}

void Pestania::setHistorial(Historial* historial1)
{
	if (this->historial != NULL)
	{
		delete this->historial;
	}
	this->historial = historial1;
}

Historial* Pestania::getHistorial()
{
	return historial;
}

void Pestania::importarHistorial(ifstream& input) {
	if (historial) {  
		historial->importarHistorial(input);
	}
}

void Pestania::exportarHistorial(ofstream& output) {
	if (historial) {
		historial->exportarHistorial(output);
	}
}
string Pestania::toString()
{
	stringstream s;
	const int width = 40;
	const int contentWidth = width - 4;
	const string border(width, '-');

	system("cls");
	s << "              NAVEGADOR WEB          " << endl;
	s << border << endl;
	s << "[ " << string(contentWidth, ' ') << " ]" << endl;
	s << "[ " << "URL: " << sitioWebActual->getUrl() << string(contentWidth - ("URL: " + sitioWebActual->getUrl()).length(), ' ') << " ]" << endl;
	s << "[ " << "Titulo: " << sitioWebActual->getTitulo() << string(contentWidth - ("Titulo: " + sitioWebActual->getTitulo()).length(), ' ') << " ]" << endl;
	s << "[ " << string(contentWidth, ' ') << " ]" << endl;
	s << border << endl;
	s << endl;
	return s.str();
}
bool Pestania::operator==(const Pestania& other) const {
	
	return sitioWebActual == other.sitioWebActual;

}
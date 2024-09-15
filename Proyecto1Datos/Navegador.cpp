#include "Navegador.h"

Navegador::Navegador()
{
  /*  sesionActual = NULL;*/
	modoIncognito = false;
    listaPestanias = new ListPestanias();
	marcadoresGuardados = list<Marcador*>();

}

Navegador::~Navegador()
{
}


void Navegador::cambiarmodoIncognito()
{
	modoIncognito = !modoIncognito;

}

//void Navegador::importarHistorial(const string& nombreHistorial)
//{
//    std::ifstream inputFile(nombreHistorial);
//    if (!inputFile.is_open()) {
//        std::cerr << "Error abriendo el archivo para importar el historial.\n";
//        return;
//    }
//
//
//    for (auto& pest : listaPestanias) {
//        if (pest->getHistorial()) {
//            pest->getHistorial()->limpiarHistorial();
//            pest->getHistorial()->importarHistorial(inputFile);
//        }
//    }
//
//    inputFile.close();
//}
//
//void Navegador::exportarHistorial(const std::string& nombreHistorial)
//{
//    std::ofstream outputFile(nombreHistorial);
//    if (!outputFile.is_open()) {
//        std::cerr << "Error abriendo el archivo para exportar el historial.\n";
//        return;
//    }
//    for (auto& pest : listaPestanias) {
//        if (pest->getHistorial()) {
//            pest->getHistorial()->exportarHistorial(outputFile);
//        }
//    }
//
//    outputFile.close();
//}

//Sesion* Navegador::getSesion()
//{
//    return sesionActual;
//}
//
//void Navegador::setSesion(Sesion* sesion)
//{
//    if (sesionActual != nullptr) {
//        delete sesionActual;
//    }
//    sesionActual = sesion;
//}

string Navegador::toString()
{
    stringstream s;
	s << "Navegador: \n";
	s << listaPestanias->toString();
    return s.str();
}

ListPestanias* Navegador::getListaPestanias()
{
    return listaPestanias;
}

list<Marcador*> Navegador::getMarcadoresGuardados()
{
    return marcadoresGuardados;
}

int Navegador::cantidadPestanias()
{
	return listaPestanias->size();
}

void Navegador::agregarPestania(Pestania* pest)
{
	listaPestanias->add(pest);
}

int Navegador::posicionDelIndex()
{
	return listaPestanias->posicionActualIndex();
}

void Navegador::pestaniaAnterior()
{
	listaPestanias->retroceder();
}

void Navegador::pestaniaSiguiente()
{
	listaPestanias->avanzar();
}

string Navegador::mostrarPestaniaActual()
{
	return listaPestanias->getPestaniaActual()->toString();
}






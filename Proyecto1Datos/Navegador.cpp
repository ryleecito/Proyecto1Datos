#include "Navegador.h"

Navegador::Navegador()
{
  /*  sesionActual = NULL;*/
	modoIncognito = false;
	listaPestanias = list<Pestania>();
	marcadoresGuardados = list<Marcador>();

}

Navegador::~Navegador()
{
}

void Navegador::nuevaPestania(Pestania* pest)
{
	listaPestanias.push_back(*pest);
}

void Navegador::cerrarPestania(Pestania* pest)
{
	listaPestanias.remove(*pest);
}

void Navegador::cambiarmodoIncognito()
{
	modoIncognito = !modoIncognito;

}

void Navegador::importarHistorial(const string& nombreHistorial)
{
    std::ifstream inputFile(nombreHistorial);
    if (!inputFile.is_open()) {
        std::cerr << "Error abriendo el archivo para importar el historial.\n";
        return;
    }


    for (auto& pest : listaPestanias) {
        if (pest.getHistorial()) {
            pest.getHistorial()->limpiarHistorial();
            pest.getHistorial()->importarHistorial(inputFile);
        }
    }

    inputFile.close();
}

void Navegador::exportarHistorial(const std::string& nombreHistorial)
{
    std::ofstream outputFile(nombreHistorial);
    if (!outputFile.is_open()) {
        std::cerr << "Error abriendo el archivo para exportar el historial.\n";
        return;
    }
    for (auto& pest : listaPestanias) {
        if (pest.getHistorial()) {  
            pest.getHistorial()->exportarHistorial(outputFile);  
        }
    }

    outputFile.close();
}

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
    for (auto& pest : listaPestanias) {
        s << pest.toString();
    }
    return s.str();
}


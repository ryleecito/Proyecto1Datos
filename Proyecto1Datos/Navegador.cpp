#include "Navegador.h"

Navegador::Navegador()
{
  /*  sesionActual = NULL;*/
	modoIncognito = false;
    listaPestanias = new ListPestanias();
	marcadoresGuardados = std::list<Marcador*>();
	sitios = std::list<SitioWeb*>();
	sitios.push_back(new SitioWeb("www.google.com", "Google","Pedro"));
	sitios.push_back(new SitioWeb("www.youtube.com", "Youtube", "Juan"));


	/*
	std::list<std::string> listaEtiquetas;
	listaEtiquetas.push_back("videos");
	SitioWeb* sitio = new SitioWeb("www.youtube.com", "YouTube", "carlos");

	Marcador* marcador = new Marcador(sitio, listaEtiquetas);
	marcadoresGuardados.push_back(marcador);*/

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

std::string Navegador::toString()
{
	std::stringstream s;
	s << "Navegador: \n";
	s << listaPestanias->toString();
    return s.str();
}

ListPestanias* Navegador::getListaPestanias()
{
    return listaPestanias;
}

std::list<Marcador*> Navegador::getMarcadoresGuardados()
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

void Navegador::agregarPaginaWeb(SitioWeb* sitio)
{
	listaPestanias->getPestaniaActual()->agregarPaginaWeb(sitio);
}

std::string Navegador::mostrarPestaniaActual()
{
	return listaPestanias->getPestaniaActual()->toString();
}

void Navegador::agregarMarcador(Marcador* marcador)
{
	 if (marcador == nullptr) {
        return;
    }
    marcadoresGuardados.push_back(marcador);
   // posicionActual = std::prev(marcadoresGuardados.end());
}

std::string Navegador::MostrarMarcadoresGuardados() const
{
	std::stringstream ss;

	ss << "=====================\n";
	ss << " Bookmarks  \n";
	ss << "=====================\n\n";

	if (marcadoresGuardados.empty()) {
		ss << "No bookmarks saved.\n";
	}
	else {
		int index = 1;
		for (auto marcador : marcadoresGuardados) {
			ss << index++ << ". " << marcador->toString() << "\n";
			ss << "---------------------\n"; 
		}
	}
	return ss.str();
}

SitioWeb* Navegador::getSitioActual()
{
	return listaPestanias->getPestaniaActual()->getHistorial()->getSitioActual();
}

SitioWeb* Navegador::buscarPaginaWeb(const std::string url)
{
	auto it = std::find_if(sitios.begin(), sitios.end(), [&](SitioWeb* sitio) {
		return sitio->getUrl() == url;
		});

	if (it != sitios.end()) {
		return *it;  
	}
	return nullptr;
}

void Navegador::paginaAnterior()
{
	listaPestanias->getPestaniaActual()->getHistorial()->retroceder();
}

void Navegador::paginaSiguiente()
{
	listaPestanias->getPestaniaActual()->getHistorial()->avanzar();
}

int Navegador::cantidadPaginas()
{
	return listaPestanias->getPestaniaActual()->getHistorial()->size();
}






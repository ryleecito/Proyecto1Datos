#include "Navegador.h"

Navegador::Navegador()
{
  /*  sesionActual = NULL;*/
	modoIncognito = false;
	listaPestaniasIncognito = new ListPestanias();
    listaPestanias = new ListPestanias();
	marcadoresGuardados = std::list<Marcador*>();
	sitios = std::list<SitioWeb*>();
	cargarArchivoSitiosWebCSV("sitiosWeb.csv");
}

Navegador::~Navegador()
{
}

std::string Navegador::toString()
{
	std::stringstream s;
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

ListPestanias* Navegador::getListaPestaniasIncognito()
{
	return listaPestaniasIncognito;
}

std::list<SitioWeb*>* Navegador::getListaSitiosW()
{
	return &sitios;
}

void Navegador::cambiarModoIncognito()
{
	if (modoIncognito == true) {
		listaPestaniasIncognito->limpiarPestanias();
	}
	modoIncognito = !modoIncognito;
}

bool Navegador::getModoIncognito()
{
	return modoIncognito;
}

int Navegador::cantidadPestanias()
{
	if (modoIncognito)
	{
		return listaPestaniasIncognito->size();
	}
	return listaPestanias->size();
}

void Navegador::agregarPestania(Pestania* pest)
{
	if (modoIncognito)
	{
		return listaPestaniasIncognito->add(pest);
	}
	listaPestanias->add(pest);
}

int Navegador::posicionDelIndex()
{
	if (modoIncognito)
	{
		return listaPestaniasIncognito->getPosicionActualIndex();
	}
	return listaPestanias->getPosicionActualIndex();
}

void Navegador::pestaniaAnterior()
{
	if (modoIncognito) {
		listaPestaniasIncognito->retroceder();
		return;
	}
	listaPestanias->retroceder();
}

void Navegador::pestaniaSiguiente()
{
	if (modoIncognito)
	{
		listaPestaniasIncognito->avanzar();
		return;
	}
	listaPestanias->avanzar();
}

void Navegador::agregarPaginaWeb(SitioWeb* sitio)
{
	if (modoIncognito) {
		listaPestaniasIncognito->getPestaniaActual()->agregarPaginaWeb(sitio);
		return;
	}
	listaPestanias->getPestaniaActual()->agregarPaginaWeb(sitio);
}

std::string Navegador::mostrarPestaniaActual()

{
	if (modoIncognito)
	{
		return listaPestaniasIncognito->getPestaniaActual()->toString();
	}
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
	ss << "       Bookmarks  \n";
	ss << "=====================\n\n";

	if (marcadoresGuardados.empty()) {
		ss << "No hay bookmarks guardados.\n";
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
	if (modoIncognito) {
		return listaPestaniasIncognito->getPestaniaActual()->getHistorial()->getSitioActual();

	}
	return listaPestanias->getPestaniaActual()->getHistorial()->getSitioActual();
}

SitioWeb* Navegador::buscarPaginaWeb(const std::string url)
{
	auto it = std::find_if(sitios.begin(), sitios.end(), [&](SitioWeb* sitio) {
		// Agregar una impresión para ver qué sitio se está comparando
		std::cout << "Comparando con sitio: " << sitio->getUrl() << std::endl;
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

	if (listaPestanias == nullptr) {
		return 0;
	}
	if (listaPestanias->getPestaniaActual() == nullptr) {
		return 0;
	}
	if (listaPestanias->getPestaniaActual()->getHistorial() == nullptr) {
		return 0;
	}

	return listaPestanias->getPestaniaActual()->getHistorial()->size();
}

void Navegador::guardarArchivoNavegador(std::ofstream& out)
{
	// guardamos el incognito
	out.write(reinterpret_cast<const char*>(&modoIncognito), sizeof(modoIncognito));

	// se guardan las listas
	listaPestanias->guardarArchivoListaPestanias(out);
	listaPestaniasIncognito->guardarArchivoListaPestanias(out);

	// guardamos marcadores
	size_t size = marcadoresGuardados.size();
	out.write(reinterpret_cast<const char*>(&size), sizeof(size));
	for (const auto& marcador : marcadoresGuardados) {
		marcador->guardarArchivoMarcador(out); 
	}
}

Navegador* Navegador::cargarArchivoNavegador(std::ifstream& in)
{
	Navegador* navegadorCargado = new Navegador();

	in.read(reinterpret_cast<char*>(&navegadorCargado->modoIncognito), sizeof(navegadorCargado->modoIncognito));

	navegadorCargado->listaPestanias = ListPestanias::cargarArchivoListaPestanias(in);
	navegadorCargado->listaPestaniasIncognito = ListPestanias::cargarArchivoListaPestanias(in);

	size_t size;
	in.read(reinterpret_cast<char*>(&size), sizeof(size));
	for (size_t i = 0; i < size; ++i) {
		Marcador* marcador = Marcador::cargarArchivoMarcador(in); 
		if (marcador) {
			navegadorCargado->agregarMarcador(marcador);
		}
	}

	return navegadorCargado;
}

void Navegador::cargarArchivoSitiosWebCSV(const std::string& rutaArchivo) {

	std::string url, titulo, atributo;
	const size_t tamanioBuffer = 2048;
	char buffer[tamanioBuffer];

	std::ifstream archivo(rutaArchivo);

	if (!archivo.is_open()) {
		std::cerr << "Error al abrir el archivo CSV: " << rutaArchivo << std::endl;
		return;
	}

	while (archivo.read(buffer, tamanioBuffer) || archivo.gcount() > 0) {
		size_t bytes = archivo.gcount();
		for (size_t i = 0; i < bytes; ++i) {
			char c = buffer[i];

			if (c == ',') {

				if (url.empty()) {
					url = atributo;
				}
				else {
					titulo = atributo;
				}
				atributo.clear();  
			}
			else if (c == '\n') {

				if (!url.empty() && !titulo.empty()) {
					SitioWeb* sitio = new SitioWeb(url, titulo, "");
					sitios.push_back(sitio);
				}

				url.clear();
				titulo.clear();
				atributo.clear();
			}
			else {
				atributo += c;
			}
		}
	}

	if (!url.empty() && !titulo.empty()) {
		SitioWeb* sitio = new SitioWeb(url, titulo, "");
		sitios.push_back(sitio);
	}

	archivo.close();
}





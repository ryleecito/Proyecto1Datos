#include "Navegador.h"

Navegador::Navegador()
{
	modoIncognito = false;
	configuracion = ConfigHistorial::getInstancia();
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
		listaPestaniasIncognito->agregarPaginaWeb(sitio);
		return;
	}
	listaPestanias->agregarPaginaWeb(sitio);
}

Pestania* Navegador::getPestaniaActual()
{
	if (modoIncognito) {
		return listaPestaniasIncognito->getPestaniaActual();
	}
	return listaPestanias->getPestaniaActual();
}

std::string Navegador::mostrarPestaniaActual()

{
	if (modoIncognito)
	{
		return listaPestaniasIncognito->mostrarPestaniaActual();
	}
	return listaPestanias->mostrarPestaniaActual();
}

bool Navegador::limpiarViejasEntradas()
{

	return listaPestanias->limpiarEntradasViejas();
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

Marcador* Navegador::buscarMarcadorPorSitio(SitioWeb* sitio)
{
	auto it = std::find_if(marcadoresGuardados.begin(), marcadoresGuardados.end(), [&](Marcador* marcador) {
		return marcador->getSitio()->getUrl() == sitio->getUrl();
		});

	if (it != marcadoresGuardados.end()) {
		return *it;
	}
	return nullptr;
}

SitioWeb* Navegador::getSitioActual()
{
	if (modoIncognito) {
		return listaPestaniasIncognito->getSitioActual();

	}
	return listaPestanias->getSitioActual();
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
	listaPestanias->irAtras();
}

void Navegador::paginaSiguiente()
{
	listaPestanias->irAdelante();
}

int Navegador::cantidadPaginas()
{

	if (listaPestanias == nullptr) {
		return 0;
	}
	if (listaPestanias->getPestaniaActual() == nullptr) {
		return 0;
	}
	if (listaPestanias->getHistorial() == nullptr) {
		return 0;
	}

	return listaPestanias->sizeHistorial();
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

	const size_t tamanioBuffer = 2048;
	char buffer[tamanioBuffer];
	std::ifstream archivo(rutaArchivo);

	if (!archivo.is_open()) {
		std::cerr << "Error al abrir el archivo CSV: " << rutaArchivo << std::endl;
		return;
	}

	std::string url, titulo, dominio;
	std::string atributo;

	while (archivo.read(buffer, tamanioBuffer) || archivo.gcount() > 0) {
		size_t bytes = archivo.gcount();
		for (size_t i = 0; i < bytes; ++i) {
			char c = buffer[i];

			if (c == ',') {

				if (url.empty()) {
					url = atributo;  
					atributo.clear();
				}
				if (titulo.empty() && !url.empty()) {
					titulo = atributo; 
					atributo.clear();
				}

			}
			else if (c == '\n') {
				dominio = atributo;
				if (!url.empty() && !titulo.empty() && !dominio.empty()) {
					SitioWeb* sitio = new SitioWeb(url, titulo, dominio);
					sitios.push_back(sitio);
				}

				url.clear();
				titulo.clear();
				dominio.clear();
				atributo.clear();
			}
			else {
				atributo += c; 
			}
		}
	}

	if (!url.empty() && !titulo.empty() && !dominio.empty()) {
		SitioWeb* sitio = new SitioWeb(url, titulo, dominio);
		sitios.push_back(sitio);
	}

	archivo.close();
}

void Navegador::limpiarPestanias()
{
	if (modoIncognito) {
		listaPestaniasIncognito->limpiarPestanias();
	}
	else {
		listaPestanias->limpiarPestanias();
	}
}

ConfigHistorial* Navegador::getConfiguraciones() const
{
	return configuracion->getInstancia();
}

void Navegador::setMaxEntradas(int max)
{
	configuracion->setMaxEntradas(max);
}

void Navegador::setTiempoMaximo(int time)
{
	configuracion->setTiempoMaximo(time);

}







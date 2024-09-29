#include "Navegador.h"


Navegador::Navegador()
{
	modoIncognito = false;
	configuracion = ConfigHistorial::getInstancia();
	listaPestaniasIncognito = new ListPestanias();
    listaPestanias = new ListPestanias();
	marcadoresGuardados = std::list<Marcador*>();
	sitios = std::vector<SitioWeb*>();
	cargarArchivoSitiosWebCSV("sitiosWeb.csv");
}

Navegador::~Navegador()
{
	delete listaPestaniasIncognito;  
	delete listaPestanias;    
	//ConfigHistorial::destruirInstancia();

	for (auto marcador : marcadoresGuardados) {
		delete marcador;               
	}
	for (auto sitio : sitios) {
		delete sitio;                
	}


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

std::vector<SitioWeb*>* Navegador::getListaSitiosW()
{
	return &sitios;
}

void Navegador::cambiarModoIncognito() {
	modoIncognito = !modoIncognito;

	if (modoIncognito) {
		listaPestaniasIncognito->limpiarPestanias();
	}

}

bool Navegador::getModoIncognito() const
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

void Navegador::agregarPestania()
{
	if (modoIncognito)
	{
		 listaPestaniasIncognito->add(new PestaniaIncognito());
		 return;
	}
	listaPestanias->add(new Pestania());
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

PestaniaAbstracta* Navegador::getPestaniaActual()
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

void Navegador::ajustarTamanoHistorial()
{
	listaPestanias->ajustarTamanoHistorial();
}


void Navegador::agregarMarcador(Marcador* marcador)
{
	 if (marcador == nullptr) {
        return;
    }
    marcadoresGuardados.push_back(marcador);
   // posicionActual = std::prev(marcadoresGuardados.end());
}

// Metodo para imprimir todos los bookmarks guardados en el navegador
// Si no hay bookmarks guardados, se imprime un mensaje indicando que no hay bookmarks guardados
std::string Navegador::mostrarMarcadoresGuardados() const
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

// Este metodo busca un marcador por el sitio web que tiene asociado
// Si no se encuentra el marcador, se retorna nullptr
// Si se encuentra el marcador, se retorna el marcador
// hace las comparaciones con la URL del sitio web asociado al marcador
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

	throw ExcepcionGenerica("404 - Not Found");

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

std::string Navegador::busquedaPalabraClave(const std::string& palabraClave)
{
	return listaPestanias->busquedaPalabraClave(palabraClave);
}

void Navegador::setFiltro(const std::string& filtro)
{
	listaPestanias->setFiltro(filtro);
	moverseAPrimeraCoincidencia();
}

void Navegador::moverseAPrimeraCoincidencia()
{
	listaPestanias->moverseAPrimeraCoincidencia();
}

void Navegador::guardarArchivoNavegador(std::ofstream& out)
{
	out.write(reinterpret_cast<const char*>(&modoIncognito), sizeof(modoIncognito));


	if (listaPestanias) {
		listaPestanias->guardarArchivoListaPestanias(out); 
	}

	size_t numMarcadores = marcadoresGuardados.size();
	out.write(reinterpret_cast<const char*>(&numMarcadores), sizeof(numMarcadores));
	for (Marcador* marcador : marcadoresGuardados) {
		if (marcador) {
			marcador->guardarArchivoMarcador(out); 
		}
	}
	ConfigHistorial* config = ConfigHistorial::getInstancia();
	config->guardarArchivoConfigHistorial(out);



}

Navegador* Navegador::cargarArchivoNavegador(std::ifstream& in) 
{
	Navegador* navegador = new Navegador();


	in.read(reinterpret_cast<char*>(&navegador->modoIncognito), sizeof(navegador->modoIncognito));

	if (navegador->listaPestanias) {
		delete navegador->listaPestanias;
		navegador->listaPestanias= ListPestanias::cargarArchivoListaPestanias(in);
	}

	size_t numMarcadores;
	in.read(reinterpret_cast<char*>(&numMarcadores), sizeof(numMarcadores));
	for (size_t i = 0; i < numMarcadores; ++i) {
		Marcador* marcador = Marcador::cargarArchivoMarcador(in);
		if (marcador) {
			navegador->marcadoresGuardados.push_back(marcador);
		}
	}

	ConfigHistorial* config = ConfigHistorial::cargarArchivoConfigHistorial(in);

	navegador->configuracion->getInstancia()->setMaxEntradas(config->getMaxEntradas());
	navegador->configuracion->getInstancia()->setTiempoMaximo(config->getTiempoMaximo());	

	return navegador;
}

// Metodo que carga los sitios web de un archivo CSV
// Si no se puede abrir el archivo, se lanza una excepcion
// Si se puede abrir el archivo, se leen las lineas del archivo
// leemos los 3 campos de la linea (url,titulo, dominio)
void Navegador::cargarArchivoSitiosWebCSV(const std::string& rutaArchivo) 
{
	std::ifstream archivo(rutaArchivo);

	if (!archivo.is_open()) {
		throw ExcepcionGenerica("Error al abrir el archivo CSV: " + rutaArchivo);
	}

	std::string linea;
	while (std::getline(archivo, linea)) {
		std::stringstream ss(linea);
		std::string url, titulo, dominio;


		if (std::getline(ss, url, ',') &&
			std::getline(ss, titulo, ',') &&
			std::getline(ss, dominio))
		{

			SitioWeb* sitio = new SitioWeb(url, titulo, dominio);
			sitios.push_back(sitio);
		}
	}

	archivo.close();
}


ConfigHistorial* Navegador::getConfiguraciones() const
{
	return configuracion->getInstancia();
}

void Navegador::setMaxEntradas(int max)
{
	configuracion->setMaxEntradas(max);
	ajustarTamanoHistorial();
}

void Navegador::setTiempoMaximo(int time)
{
	configuracion->setTiempoMaximo(time);
	limpiarViejasEntradas();
}

// Metodo que reinicia las configuraciones del historial
// Se reinicia el maximo de entradas y el tiempo maximo a -1 (que es cuando no hay configs)

void Navegador::reiniciarConfiguraciones()
{
	configuracion->setMaxEntradas(-1);
	ajustarTamanoHistorial();
	configuracion->setTiempoMaximo(-1);
	limpiarViejasEntradas();
}







#include "ListaPestanias.h"

ListPestanias::ListPestanias()
    : posicionActual(pestanias.end()), posicionActualIdx(-1) {}

ListPestanias::~ListPestanias() {
    limpiarPestanias();
}

int ListPestanias::size() const {
    return (int)pestanias.size();
}

void ListPestanias::add(Pestania* pestania) {

    pestanias.push_back(pestania);
    posicionActual = std::prev(pestanias.end());  
    posicionActualIdx = (int)pestanias.size() - 1;
}

void ListPestanias::retroceder() {

    if (pestanias.empty() || posicionActual == pestanias.begin()) {
        return;
    }

    if (posicionActual != pestanias.begin()) {
        --posicionActual;
        --posicionActualIdx;  
    }
}

void ListPestanias::avanzar() {

    if (pestanias.empty() || posicionActual == pestanias.end()) {
        return;
    }

    if (posicionActual != std::prev(pestanias.end())) {
        ++posicionActual;
        ++posicionActualIdx;
    }
}

void ListPestanias::limpiarPestanias() {
    for (auto& pestania : pestanias) {
        delete pestania;  
    }
    pestanias.clear();   
    posicionActual = pestanias.end();
    posicionActualIdx = -1;  
}

int ListPestanias::getPosicionActualIndex() const {
    return posicionActualIdx; 
}

std::string ListPestanias::toString() const {


    std::stringstream s;
    for (const auto& pestania : pestanias) {
        s << pestania->toString() << std::endl;
    }
    return s.str();
}

std::list<Pestania*> ListPestanias::getPestanias() const {
    return pestanias;
}

Pestania* ListPestanias::getPestaniaActual() const {
    if (posicionActual != pestanias.end()) {
        return *posicionActual;
    }
    return nullptr;
}

Historial* ListPestanias::getHistorial() const
{
    if (posicionActual != pestanias.end()) {
        return (*posicionActual)->getHistorial();
    }
    return nullptr;
}

void ListPestanias::agregarPaginaWeb(SitioWeb* sitio) {
    if (posicionActual != pestanias.end()) {
        (*posicionActual)->agregarPaginaWeb(sitio);
    }
}

std::string ListPestanias::mostrarPestaniaActual() const
{
    if (posicionActual != pestanias.end()) {
        return (*posicionActual)->toString();
    }
    return "";
}

void ListPestanias::guardarArchivoListaPestanias(std::ofstream& out)
{
    size_t size = pestanias.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size)); 

    for (Pestania* pestania : pestanias) {
        pestania->guardarArchivoPestania(out);
    }
}

ListPestanias* ListPestanias::cargarArchivoListaPestanias(std::ifstream& in)
{
    ListPestanias* listaCargada = new ListPestanias(); 
    size_t size = 0;
    in.read(reinterpret_cast<char*>(&size), sizeof(size)); 

    for (size_t i = 0; i < size; ++i) {
        Pestania* pestania = Pestania::cargarArchivoPestania(in); 
        if (pestania) {
            listaCargada->add(pestania);
        }
    }
    return listaCargada; 
}

SitioWeb* ListPestanias::getSitioActual() const
{
    if (posicionActual != pestanias.end()) {
		return (*posicionActual)->getSitioActual();
	}
    return nullptr;
}

bool ListPestanias::limpiarEntradasViejas()
{


    bool entradasBorradas = false; 

    for (auto& pestania : pestanias) { 

        if (pestania->limpiarEntradasViejas()) {
            entradasBorradas = true;
        }
    }

    return entradasBorradas;
}

void ListPestanias::setFiltro(const std::string& filtro)
{
    if (posicionActual != pestanias.end()) {
        (*posicionActual)->setFiltro(filtro);
    }
}

void ListPestanias::ajustarTamanoHistorial()
{
    for (auto& pestania : pestanias) {
		pestania->ajustarTamanoHistorial();
	}
}

std::string ListPestanias::busquedaPalabraClave(const std::string& palabraClave)
{
    if (posicionActual != pestanias.end()) {
        return (*posicionActual)->busquedaPalabraClave(palabraClave);
    }
    return "";
}

void ListPestanias::moverseAPrimeraCoincidencia()
{
    if (posicionActual != pestanias.end()) {
	    (*posicionActual)->moverseAPrimeraCoincidencia();
    }
}

int ListPestanias::sizeHistorial() const
{
    if (posicionActual != pestanias.end()) {
        return (*posicionActual)->sizeHistorial();
    }
    return 0;
}

void ListPestanias::irAtras()
{
    if (posicionActual != pestanias.end()) {
		(*posicionActual)->irAtras();
	}
}

void ListPestanias::irAdelante()
{
    if (posicionActual != pestanias.end()) {
		(*posicionActual)->irAdelante();
	}
}

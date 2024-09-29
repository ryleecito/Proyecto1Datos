#include "ListaPestanias.h"

ListPestanias::ListPestanias()
    : posicionActual(pestanias.end()), posicionActualIdx(-1) {}

ListPestanias::~ListPestanias() {
    limpiarPestanias();
    std::cout << "Lista pestanias eliminada" << std::endl;
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

    if (!pestanias.empty()) {
        for (auto& pestania : pestanias) {
            delete pestania;
        }

    }
    pestanias.clear();
    posicionActual = pestanias.end();
    posicionActualIdx = -1;  
}

void ListPestanias::reiniciar() {
    if (!pestanias.empty()) {
        posicionActual = pestanias.begin();
        posicionActualIdx = 0;
    }
    else {
        posicionActual = pestanias.end();
        posicionActualIdx = -1;
    }
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

    size_t numPestanias = pestanias.size();
    out.write(reinterpret_cast<const char*>(&numPestanias), sizeof(numPestanias));

    for (Pestania* pestania : pestanias) {
        if (pestania) {
            pestania->guardarArchivoPestania(out); 
        }
    }

    out.write(reinterpret_cast<const char*>(&posicionActualIdx), sizeof(posicionActualIdx));
}


ListPestanias* ListPestanias::cargarArchivoListaPestanias(std::ifstream& in)
{
    ListPestanias* nuevaLista = new ListPestanias(); // Crear un nuevo objeto ListPestanias
    size_t numPestanias;
    in.read(reinterpret_cast<char*>(&numPestanias), sizeof(numPestanias));

    for (size_t i = 0; i < numPestanias; ++i) {
        Pestania* pestania = Pestania::cargarArchivoPestania(in); 
        nuevaLista->add(pestania);

    }

    size_t posicionActualIdx;
    in.read(reinterpret_cast<char*>(&nuevaLista->posicionActualIdx), sizeof(nuevaLista->posicionActualIdx));

    if (nuevaLista->posicionActualIdx < nuevaLista->pestanias.size()) {
        nuevaLista->posicionActual = nuevaLista->pestanias.begin(); 
        for (size_t i = 0; i < nuevaLista->posicionActualIdx; ++i) {
            ++nuevaLista->posicionActual; 
        }
    }
    else {
        nuevaLista->posicionActual = nuevaLista->pestanias.end(); 
    }

    return nuevaLista; 
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

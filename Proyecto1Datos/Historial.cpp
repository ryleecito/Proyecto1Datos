#include "Historial.h"
#include "ConfigHistorial.h"
#include <sstream>
#include <algorithm>


Historial::Historial() : posicionActual(historial.end()), filtro("") 
{
}

Historial::~Historial() 
{
    limpiarHistorial();
  
}

int Historial::size() const 
{
    return (int)historial.size();
}

void Historial::add(SitioWeb* sitioWeb)
{

    //El proceso de aniadir es el siguiente
    //Si la lista está vacía, se añade el sitio web de manera directa

    if (historial.empty()) {
        historial.push_back(new SitioWeb(*sitioWeb));
        posicionActual = std::prev(historial.end());
        filtro = "";
        return;
    }

    //si no esta vacía mediante este metodo se le busca y elimina si ya existe

    eliminarSitioSiExiste(sitioWeb);

    //Se obtiene el maximo de entradas permitidas en el historial llamando a una instancia de ConfigHistorial

    int maxEntradas = ConfigHistorial::getInstancia()->getMaxEntradas();

    if (historial.size() >= maxEntradas) {
        delete historial.front();// Se elimina el primer sitio web ingresado, primero liberamos la memoria, debido a que una lista de punteros
        historial.pop_front();//Seguidamente le hacemos pop de la lista de historial
    }

    //Una vez se elimina el primer sitio web (o no en caso de que no haya maximo de entradas o no se halla llegado al maximo de entradas)
    //Se añade el sitio web al final de la lista de historial

    historial.push_back(new SitioWeb(*sitioWeb));
    posicionActual = std::prev(historial.end());
    filtro = "";
}

void Historial::eliminarSitioSiExiste(SitioWeb* site) 
{
    //Se recorre la lista de historial, si el sitio web ya existe, se elimina de la lista de historial

    for (auto iter = historial.begin(); iter != historial.end(); ++iter) {
        if ((*iter)->getUrl() == site->getUrl()) {
            delete* iter;        
            historial.erase(iter); 
            return;
        }
    }
}


void Historial::retroceder()
{
    //En el retroceder se verifica primero si la lista esta vacia
    //o en su caso si la posicion actual es igual a la primera posicion de la lista 
    //si es asi pues no se hace nada

    if (historial.empty() || posicionActual == historial.begin()) {
        return; 
    }

    //Si no tiene filtro se retrocede el iterador una vez


    if (filtro.empty()) {

        --posicionActual; 
        return;
    }

    //Si tiene filtro entonces vemos a la posicion anterior

    auto posicionAnterior = std::prev(posicionActual);

    while (posicionAnterior != historial.begin()) {

        // verificamos mientras la posicionanterior no coincida con el filtro
        // entonces se retrocede el iterador (todo esto mientras no se llegue al inicio de la lista)

        if ((*posicionAnterior)->getTitulo().find(filtro) != std::string::npos || //cabe aclarar que si el find es diferente de npos significa que si se encontro la coincidencia
            (*posicionAnterior)->getUrl().find(filtro) != std::string::npos) {//esto significa que es una posicion invalida o fuera de rango de la cadena
            posicionActual = posicionAnterior; //si coincide la posicion actual apuntara a la coincidencia
            return;
        }
        posicionAnterior = --posicionAnterior; 
    }

    //Si no se encontro ninguna coincidencia entonces la posicion actual sera el inicio de la lista en caso de que esta coincida con el filtro

    if ((*historial.begin())->getTitulo().find(filtro) != std::string::npos ||
        (*historial.begin())->getUrl().find(filtro) != std::string::npos) {
        posicionActual = historial.begin(); 
    }
}

void Historial::avanzar() {

    //Mismo caso que en retroceder se verifica si esta vacia pero la diferencia es ahora si es el final
    if (historial.empty() || posicionActual == historial.end()) {
        return; 
    }

    if (filtro.empty()) {

        if (posicionActual != prev(historial.end()))
            ++posicionActual;
        return;
    }

    //En este caso se toma la posicion siguiente
    auto posicionSiguiente = std::next(posicionActual);


    while (posicionSiguiente != historial.end()) {

        //Se avanza mientras sea diferente de end

        if ((*posicionSiguiente)->getTitulo().find(filtro) != std::string::npos ||
            (*posicionSiguiente)->getUrl().find(filtro) != std::string::npos) {
            posicionActual = posicionSiguiente;// si coincide la posicion actual apuntara a la coincidencia
            return;
        }
        ++posicionSiguiente; 
    }

}

void Historial::limpiarHistorial() 
{
    for (SitioWeb* sitio : historial) {
        delete sitio;
    }
    historial.clear();
    posicionActual = historial.end();
}

std::string Historial::busquedaPalabraClave(const std::string& palabraClave) const
{
    std::stringstream s;
    int contador = 1;
    std::string palabraFiltrada = palabraClave;

    transform(palabraFiltrada.begin(), palabraFiltrada.end(), palabraFiltrada.begin(), ::tolower);

    for (SitioWeb* sitio : historial) {
        if (sitio != nullptr) {
 
            std::string tituloSitio = sitio->getTitulo();
            transform(tituloSitio.begin(), tituloSitio.end(), tituloSitio.begin(), ::tolower);

            if (tituloSitio.find(palabraFiltrada) != std::string::npos) {
                s << "------------------------------------------------------" << std::endl;
                s << " COINCIDENCIA # " << contador << std::endl;
                s << sitio->toString() << std::endl;
                contador++;
                s << "------------------------------------------------------" << std::endl;
            }
        }
    }

    return s.str(); 
}
std::list<SitioWeb*> Historial::getHistorial() const 
{
    return historial;
}

SitioWeb* Historial::getSitioActual() const
{
    if (posicionActual != historial.end() && !historial.empty()) {
        return *posicionActual;
    }
    return nullptr;
}

std::string Historial::toString() const {
    std::stringstream ss;
    ss << "Historial:\n";

    for (const auto sitio : historial) {
        ss << sitio->toString() << "\n";
    }

    return ss.str();
}

void Historial::ajustarTamanoHistorial() 
{

    if (historial.empty()) {
        return;
    }

    int maxEntradas = ConfigHistorial::getInstancia()->getMaxEntradas();
    bool posicionActualEliminada = false;

    if (maxEntradas <= 0) {
        return;
    }

    filtro = "";

    while (historial.size() > maxEntradas) {
        if (posicionActual == historial.begin()) {
            posicionActualEliminada = true;
        }

        delete historial.front();
        historial.pop_front();

        if (posicionActual == historial.begin()) {

            ++posicionActual;
        }
    }

    if (historial.empty()) {
        posicionActual = historial.end();
        return; 
    }

    if (posicionActualEliminada || posicionActual == historial.end()) {
        posicionActual = --historial.end(); 
    }
}

bool Historial::limpiarEntradasViejas()
{
    if (historial.empty()) {
        return false; 
    }

    //Obtenemos el tiempo configurado para eliminar las entradas del historial
    //Si este esta en su calor predeterminado (-1) significa que esto no esta configurado entonces no se hace nada

    int tiempoMaximo = ConfigHistorial::getInstancia()->getTiempoMaximo();
    if (tiempoMaximo <= 0) {
        return false; 
    }

    //Este es un valor bool que se retornara para saber si se eliminaron entradas del historial
    bool entradasBorradas = false;

    auto posicionOriginal = posicionActual;

    //Recorremos el historial y eliminamos las entradas que tengan un tiempo mayor al tiempo maximo configurado

    for (auto it = historial.begin(); it != historial.end(); ) {
        SitioWeb* sitio = *it;

        double diff = static_cast<double>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - sitio->getTiempoDeIngreso()).count());

        if (diff > tiempoMaximo) {
            delete sitio;         
            it = historial.erase(it); 
            entradasBorradas = true;  
        }
        else {
            ++it; 
        }
    }


    if (historial.empty()) {
        posicionActual = historial.end(); 
    }
    else if (posicionActual == historial.end() || posicionActual == posicionOriginal) {
        posicionActual = --historial.end(); 
    }

    return entradasBorradas; 
}

std::string Historial::getFiltro()
{
    return filtro;
}

void Historial::setFiltro(std::string filtro)
{
	this->filtro = filtro;
}


void Historial::moverseAPrimeraCoincidencia()
{
    // Si el historial esta vacio no hacemos nada
    if (historial.empty()) {
        return;
    }

    // Si el filtro esta vacio no hacemos nada
    if (filtro.empty()) {
        return;
    }

    // Creamos una variable para saber si se encontro una coincidencia
    // dentro del historial
    bool coincidenciaEncontrada = false;

    // Este ciclo recorre el historial y busca la primera coincidencia
    for (auto it = historial.begin(); it != historial.end(); ++it) {
        if ((*it)->getTitulo().find(filtro) != std::string::npos ||
            (*it)->getUrl().find(filtro) != std::string::npos) { 
            posicionActual = it; // Movemos la posicion actual a la primera coincidencia
            coincidenciaEncontrada = true; // Cambiamos la variable de que si encontramos una coincidencia
            break;
        }
    }

    // Si no se encontro una coincidencia, movemos la posicion actual al final
    if (!coincidenciaEncontrada) {
        posicionActual = historial.end();
    }
}

Historial* Historial::cargarArchivoHistorial(std::ifstream& in)
{
    Historial* nuevoHistorial = new Historial();

    size_t historialSize;
    in.read(reinterpret_cast<char*>(&historialSize), sizeof(historialSize));

    for (size_t i = 0; i < historialSize; ++i) {
        SitioWeb* sitio = SitioWeb::cargarArchivoSitioWeb(in);
        nuevoHistorial->add(sitio);
        delete sitio;
    }

    size_t posicionActualIdx;
    in.read(reinterpret_cast<char*>(&posicionActualIdx), sizeof(posicionActualIdx));

    if (posicionActualIdx < nuevoHistorial->historial.size()) {
        nuevoHistorial->posicionActual = nuevoHistorial->historial.begin();
        std::advance(nuevoHistorial->posicionActual, posicionActualIdx);
    }
    else {
        nuevoHistorial->posicionActual = nuevoHistorial->historial.end();
    }

    size_t filtroLength;
    in.read(reinterpret_cast<char*>(&filtroLength), sizeof(filtroLength));
    nuevoHistorial->filtro.resize(filtroLength);
    in.read(&nuevoHistorial->filtro[0], filtroLength);


    return nuevoHistorial;
}

void Historial::guardarArchivoHistorial(std::ofstream& out)
{
    size_t historialSize = historial.size();
    out.write(reinterpret_cast<const char*>(&historialSize), sizeof(historialSize));

    for (SitioWeb* sitio : historial) {
        if (sitio) {
            sitio->guardarArchivoSitioWeb(out); 
        }
    }

    auto posicionActualIdx = std::distance(historial.begin(), posicionActual);
    out.write(reinterpret_cast<const char*>(&posicionActualIdx), sizeof(posicionActualIdx));

    size_t filtroLength = filtro.size();
    out.write(reinterpret_cast<const char*>(&filtroLength), sizeof(filtroLength));
    out.write(filtro.c_str(), filtroLength);  
}


std::string Historial::getUrlActual() const
{
    if (posicionActual != historial.end()) {
        return (*posicionActual)->getUrl();
    }
    return "";
}

std::string Historial::getTituloActual() const
{
    if (posicionActual != historial.end()) {
		return (*posicionActual)->getTitulo();
	}
    return "";
}

std::string Historial::getDominioActual() const
{
    if (posicionActual != historial.end()) {
		return (*posicionActual)->getDominio();
	}
	return "";
}





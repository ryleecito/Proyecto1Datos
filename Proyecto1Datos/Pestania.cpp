#include "Pestania.h"

Pestania::Pestania()
    : historial(new Historial())
{
}

Pestania::Pestania(Historial* historial)
    : historial(historial) 
{
}

Pestania::Pestania(const Pestania&)
{
    this->historial = new Historial();
}

Pestania::~Pestania()
{
    delete historial; 
}

int Pestania::sizeHistorial() const
{
    return historial->size();
}


void Pestania::irAtras()
{
    historial->retroceder();
}

void Pestania::irAdelante()
{
    historial->avanzar();
}



SitioWeb* Pestania::getSitioActual() const
{
    return historial->getSitioActual();
}

void Pestania::ajustarTamanoHistorial()
{
    historial->ajustarTamanoHistorial();
}

bool Pestania::limpiarEntradasViejas()
{
    return historial->limpiarEntradasViejas();
}

std::string Pestania::busquedaPalabraClave(const std::string& palabraClave)
{
	return historial->busquedaPalabraClave(palabraClave);
}

void Pestania::moverseAPrimeraCoincidencia()
{
	historial->moverseAPrimeraCoincidencia();
}

void Pestania::setFiltro(const std::string& filtro)
{
    historial->setFiltro(filtro);
}

std::string Pestania::getUrlActual() const
{
    return historial->getUrlActual();
}

std::string Pestania::getTituloActual() const
{
    return  historial->getTituloActual();
}

std::string Pestania::getDominioActual() const
{
    return historial->getDominioActual();
}



void Pestania::setHistorial(Historial* historial1)
{
    if (this->historial != nullptr)
    {
        delete this->historial;
    }
    this->historial = historial1; 
}

Historial* Pestania::getHistorial() const
{
    return historial;
}

void Pestania::agregarPaginaWeb(SitioWeb* sitio)
{
    historial->add(sitio);
}

std::string Pestania::toString() const
{
    std::stringstream s;
    const int width = 40;
    const int contentWidth = width - 4;
    const std::string border(width, '-');

    if (historial->getSitioActual() != nullptr) {
        s << "              NAVEGADOR WEB          " << std::endl;
        s << border << std::endl;
        s << "[ " << std::string(contentWidth, ' ') << " ]" << std::endl;
        s << "[ " << "URL: " << getUrlActual()
            << std::string(contentWidth - ("URL: " + getUrlActual()).length(), ' ') << " ]" << std::endl;
        s << "[ " << "Titulo: " << getTituloActual()
            << std::string(contentWidth - ("Titulo: " + getTituloActual()).length(), ' ') << " ]" << std::endl;
        s << "[ " << "Dominio: " << getDominioActual()
            << std::string(contentWidth - ("Dominio: " + getDominioActual()).length(), ' ') << " ]" << std::endl;
        s << "[ " << std::string(contentWidth, ' ') << " ]" << std::endl;
        s << border << std::endl;
        s << std::endl;


        
    }
    else {
        s << "              NAVEGADOR WEB          " << std::endl;
        s << border << std::endl;
        s << "[ " << std::string(contentWidth, ' ') << " ]" << std::endl;
        s << "[ No hay sitio actual disponible       ]" << std::endl; 
        s << "[ " << std::string(contentWidth, ' ') << " ]" << std::endl;
        s << border << std::endl;
        s << std::endl;

        s << "Yo soy esta pestaña: " << this << std::endl;
        s << std::endl;
    }

    return s.str();
}

// la pestania siempre tendra un historia asignado entonces no hay
// necesidad de verificar si es nullptr
void Pestania::guardarArchivoPestania(std::ofstream& out)
{
    historial->guardarArchivoHistorial(out); 
}

Pestania* Pestania::cargarArchivoPestania(std::ifstream& in)
{
    Historial* historialCargado = Historial::cargarArchivoHistorial(in);
    return new Pestania(historialCargado);
}


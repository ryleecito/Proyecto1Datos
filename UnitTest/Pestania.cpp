#include "Pestania.h"



Pestania::Pestania()
    : historial(new Historial())
{
}

Pestania::Pestania(Historial* historial)
    : historial(historial) 
{
}

Pestania::~Pestania()
{
    delete historial; 
}

void Pestania::irAtras()
{
    historial->retroceder();
}

void Pestania::irAdelante()
{
    historial->avanzar();
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
        s << "[ " << "URL: " << historial->getSitioActual()->getUrl()
            << std::string(contentWidth - ("URL: " + historial->getSitioActual()->getUrl()).length(), ' ') << " ]" << std::endl;
        s << "[ " << "Titulo: " << historial->getSitioActual()->getTitulo()
            << std::string(contentWidth - ("Titulo: " + historial->getSitioActual()->getTitulo()).length(), ' ') << " ]" << std::endl;
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

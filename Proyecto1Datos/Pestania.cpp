#include "Pestania.h"

Pestania::Pestania()
    : historial(new Historial()) // Usa lista de inicialización
{
}

Pestania::Pestania(Historial* historial)
    : historial(historial) // Usa lista de inicialización
{
}

Pestania::~Pestania()
{
    delete historial; // No es necesario verificar si es nullptr
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
    this->historial = historial1; // No usamos `new`, simplemente reasignamos el puntero
}

Historial* Pestania::getHistorial() const
{
    return historial;
}

void Pestania::importarHistorial(std::ifstream& input)
{
    if (historial)
    {
        historial->importarHistorial(input);
    }
}

void Pestania::exportarHistorial(std::ofstream& output)
{
    if (historial)
    {
        historial->exportarHistorial(output);
    }
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
        s << "[ No hay sitio actual disponible       ]" << std::endl; // Mensaje si no hay sitio actual
        s << "[ " << std::string(contentWidth, ' ') << " ]" << std::endl;
        s << border << std::endl;
        s << std::endl;
    }

    return s.str();
}

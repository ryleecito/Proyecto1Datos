#include "Marcador.h"

Marcador::Marcador() : sitio(nullptr) // Inicializaci�n de sitio a nullptr
{
}

Marcador::Marcador(SitioWeb* sitio, const std::string eti)
    : sitio(sitio), etiqueta(eti) // Inicializaci�n de miembro
{
}

Marcador::~Marcador()
{
    // Si el puntero 'sitio' apunta a un objeto que debe ser eliminado aqu�, hazlo.
    // Pero normalmente, el puntero 'sitio' deber�a ser manejado por otro objeto o clase.
    // Por ahora, dejaremos esto vac�o.
}

SitioWeb* Marcador::getSitio() const
{
    return sitio;
}

std::string Marcador::toString() const
{
    std::stringstream ss;
    ss << "Marcador:\n";

    if (sitio != nullptr) {
        ss << "  Sitio Web: " << sitio->toString() << "\n";
    }
    else {
        ss << "  Sitio Web: (sin sitio asignado)\n";
    }

    ss << "  Etiqueta: ";
        ss << etiqueta << " ";

    return ss.str();
}

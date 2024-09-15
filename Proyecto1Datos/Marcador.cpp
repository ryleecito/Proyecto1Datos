#include "Marcador.h"

Marcador::Marcador() : sitio(nullptr) // Inicialización de sitio a nullptr
{
}

Marcador::Marcador(SitioWeb* sitio, const std::list<std::string>& listaEtiquetas)
    : sitio(sitio), listaEtiquetas(listaEtiquetas) // Inicialización de miembro
{
}

Marcador::~Marcador()
{
    // Si el puntero 'sitio' apunta a un objeto que debe ser eliminado aquí, hazlo.
    // Pero normalmente, el puntero 'sitio' debería ser manejado por otro objeto o clase.
    // Por ahora, dejaremos esto vacío.
}

void Marcador::agregarEtiqueta(const std::string& etiqueta)
{
    listaEtiquetas.push_back(etiqueta);
}

void Marcador::eliminarEtiqueta(const std::string& etiqueta)
{
    listaEtiquetas.remove(etiqueta);
}

SitioWeb* Marcador::getSitio() const
{
    return sitio;
}

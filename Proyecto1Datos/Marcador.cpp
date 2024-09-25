#include "Marcador.h"

Marcador::Marcador() : sitio(nullptr)
{
}

Marcador::Marcador(SitioWeb* sitio, const std::string eti)
    : sitio(sitio), etiqueta(eti) 
{
}

Marcador::~Marcador()
{
    // Si el puntero 'sitio' apunta a un objeto que debe ser eliminado aquí, hazlo.
    // Pero normalmente, el puntero 'sitio' debería ser manejado por otro objeto o clase.
    // Por ahora, dejaremos esto vacío.
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

void Marcador::guardarArchivoMarcador(std::ofstream& out)
{
	if (sitio != nullptr)
	{
		sitio->guardarArchivoSitioWeb(out);
	}
    size_t etiquetaTam = etiqueta.size();
    out.write(reinterpret_cast<const char*>(&etiquetaTam), sizeof(etiquetaTam));
    out.write(etiqueta.c_str(), etiquetaTam);
}

Marcador* Marcador::cargarArchivoMarcador(std::ifstream& in)
{
    SitioWeb* sitio = SitioWeb::cargarArchivoSitioWeb(in);

	size_t etiquetaTam;
    in.read(reinterpret_cast<char*>(&etiquetaTam), sizeof(etiquetaTam));
    std::string etiqueta(etiquetaTam, ' ');
    in.read(&etiqueta[0], etiquetaTam);
	
	return new Marcador(sitio, etiqueta);
}

#include "Marcador.h"
#include <sstream>
#include <algorithm> 

Marcador::Marcador() : sitio(nullptr)
{
}

Marcador::Marcador(SitioWeb* sitio, const std::list<std::string*>& etis)
    : sitio(sitio), etiquetas(etis) 
{
}

Marcador::Marcador(SitioWeb* sitio, const std::string& etiqueta)
{
	this->sitio = sitio;
	etiquetas.push_back(new std::string(etiqueta));

}

Marcador::~Marcador()
{
   
    std::for_each(etiquetas.begin(), etiquetas.end(), [](std::string* et) {
        delete et;
        });
}

void Marcador::anadirEtiqueta(const std::string& etiqueta)
{
	etiquetas.push_back(new std::string(etiqueta));
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

    ss << "  Etiquetas: ";
    for (const auto& etiqueta : etiquetas) {
        if (etiqueta != nullptr) {
            ss << *etiqueta << " "; 
        }
    }

    return ss.str();
}

void Marcador::guardarArchivoMarcador(std::ofstream& out)
{
    if (sitio != nullptr) {
        sitio->guardarArchivoSitioWeb(out);
    }

    size_t numEtiquetas = etiquetas.size();
    out.write(reinterpret_cast<const char*>(&numEtiquetas), sizeof(numEtiquetas));


    for (const auto& etiqueta : etiquetas) {
        if (etiqueta != nullptr) {
            size_t etiquetaTam = etiqueta->size();
            out.write(reinterpret_cast<const char*>(&etiquetaTam), sizeof(etiquetaTam));
            out.write(etiqueta->c_str(), etiquetaTam);
        }
    }
}

Marcador* Marcador::cargarArchivoMarcador(std::ifstream& in)
{
    SitioWeb* sitio = SitioWeb::cargarArchivoSitioWeb(in);

    size_t numEtiquetas;
    in.read(reinterpret_cast<char*>(&numEtiquetas), sizeof(numEtiquetas));

 
    std::list<std::string*> etiquetasCargadas;
    for (size_t i = 0; i < numEtiquetas; ++i) {
        size_t etiquetaTam;
        in.read(reinterpret_cast<char*>(&etiquetaTam), sizeof(etiquetaTam));
        std::string* etiqueta = new std::string(etiquetaTam, ' ');
        in.read(&(*etiqueta)[0], etiquetaTam);
        etiquetasCargadas.push_back(etiqueta);
    }

    return new Marcador(sitio, etiquetasCargadas);
}

const std::list<std::string*>& Marcador::getEtiquetas() const
{
	return etiquetas;
}

void Marcador::setEtiquetas(const std::list<std::string*>& nuevasEtiquetas)
{
	etiquetas = nuevasEtiquetas;
}

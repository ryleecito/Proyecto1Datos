#include "Marcador.h"
#include <sstream>
#include <algorithm> 

Marcador::Marcador() : sitio(new SitioWeb())
{
}
Marcador::Marcador(SitioWeb* sitio, const std::list<std::string>& etiquetas) : sitio(sitio), etiquetas(etiquetas)
{
}
Marcador::Marcador(SitioWeb* sitio, const std::string& etiqueta): sitio(new SitioWeb(*sitio)) {
    etiquetas.push_back(etiqueta); 
}

Marcador::~Marcador()
{
    delete sitio;
}
void Marcador::anadirEtiqueta(const std::string& etiqueta)
{
	etiquetas.push_back(etiqueta);
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
    for (std::string etiqueta : etiquetas) {
        ss << etiqueta << " "; 
    }

    return ss.str();
}

void Marcador::guardarArchivoMarcador(std::ofstream& out) {

    sitio->guardarArchivoSitioWeb(out);

    size_t numEtiquetas = etiquetas.size();
    out.write(reinterpret_cast<const char*>(&numEtiquetas), sizeof(numEtiquetas));
    for (const auto& etiqueta : etiquetas) {
        size_t etiquetaLength = etiqueta.length();
        out.write(reinterpret_cast<const char*>(&etiquetaLength), sizeof(etiquetaLength));
        out.write(etiqueta.c_str(), etiquetaLength);
    }
}

Marcador* Marcador::cargarArchivoMarcador(std::ifstream& in) {
    SitioWeb* sitio = SitioWeb::cargarArchivoSitioWeb(in);
    std::list<std::string> etiquetas;

    size_t numEtiquetas;
    in.read(reinterpret_cast<char*>(&numEtiquetas), sizeof(numEtiquetas));
    for (size_t i = 0; i < numEtiquetas; ++i) {
        size_t etiquetaLength;
        in.read(reinterpret_cast<char*>(&etiquetaLength), sizeof(etiquetaLength));
        std::string etiqueta(etiquetaLength, ' ');
        in.read(&etiqueta[0], etiquetaLength);
        etiquetas.push_back(etiqueta);
    }

    return new Marcador(sitio, etiquetas);
}
const std::list<std::string> Marcador::getEtiquetas() const
{
	return etiquetas;
}

void Marcador::setEtiquetas(const std::list<std::string> nuevasEtiquetas)
{
	etiquetas = nuevasEtiquetas;
}

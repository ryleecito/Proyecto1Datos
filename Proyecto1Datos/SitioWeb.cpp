#include "SitioWeb.h"
const size_t MAX_LENGTH = 2048;

SitioWeb::SitioWeb() : url(""), titulo(""), dominio("") {
    tiempoDeIngreso = std::chrono::system_clock::now();
}

SitioWeb::SitioWeb(std::string url, std::string titulo, std::string dominio)
    : url(url), titulo(titulo), dominio(dominio) {
    tiempoDeIngreso = std::chrono::system_clock::now();
}

SitioWeb::SitioWeb(const SitioWeb& other)
    : url(other.url), titulo(other.titulo), dominio(other.dominio) {
    tiempoDeIngreso = std::chrono::system_clock::now();
}

SitioWeb::~SitioWeb()
{
    std::cout << "sitioweb borrado"<<titulo << std::endl;
}

std::string SitioWeb::getUrl() const
{
    return url;
}

std::string SitioWeb::getTitulo()const
{
    return titulo;
}

std::string SitioWeb::getDominio()const
{
    return dominio;
}

void SitioWeb::setUrl(std::string url)
{
    this->url = url;
}

void SitioWeb::setTitulo(std::string titulo)
{
    this->titulo = titulo;
}

void SitioWeb::setDominio(std::string dominio)
{
    this->dominio = dominio;
}

std::string SitioWeb::toString() const
{
    std::stringstream s;
    s << "URL: " << url << " Titulo: " << titulo << " Dominio: " << dominio;
    return s.str();
}

std::chrono::time_point<std::chrono::system_clock> SitioWeb::getTiempoDeIngreso() const
{
    return tiempoDeIngreso;
}

void SitioWeb::setTiempoDeIngreso(std::chrono::time_point<std::chrono::system_clock> tiempoDeIngreso)
{
	this->tiempoDeIngreso = tiempoDeIngreso;
}

void SitioWeb::guardarArchivoSitioWeb(std::ofstream& out)
{
    size_t urlLength = url.length();
    out.write(reinterpret_cast<const char*>(&urlLength), sizeof(urlLength));
    out.write(url.c_str(), urlLength);

    size_t tituloLength = titulo.length();
    out.write(reinterpret_cast<const char*>(&tituloLength), sizeof(tituloLength));
    out.write(titulo.c_str(), tituloLength);

    size_t dominioLength = dominio.length();
    out.write(reinterpret_cast<const char*>(&dominioLength), sizeof(dominioLength));
    out.write(dominio.c_str(), dominioLength);


    auto tiempoEpoch = tiempoDeIngreso.time_since_epoch().count();
    out.write(reinterpret_cast<const char*>(&tiempoEpoch), sizeof(tiempoEpoch));

}

SitioWeb* SitioWeb::cargarArchivoSitioWeb(std::ifstream& in)
{
    size_t urlTama, tituloTama, dominioTama;

    in.read(reinterpret_cast<char*>(&urlTama), sizeof(urlTama));
    std::string url(urlTama, ' ');
    in.read(&url[0], urlTama);

    in.read(reinterpret_cast<char*>(&tituloTama), sizeof(tituloTama));
    std::string titulo(tituloTama, ' ');
    in.read(&titulo[0], tituloTama);

    in.read(reinterpret_cast<char*>(&dominioTama), sizeof(dominioTama));
    std::string dominio(dominioTama, ' ');
    in.read(&dominio[0], dominioTama);

    SitioWeb* sitio = new SitioWeb(url, titulo, dominio);

    decltype(std::chrono::system_clock::now().time_since_epoch().count()) tiempoEpoch;
    in.read(reinterpret_cast<char*>(&tiempoEpoch), sizeof(tiempoEpoch));
    sitio->setTiempoDeIngreso(std::chrono::system_clock::time_point(std::chrono::system_clock::duration(tiempoEpoch)));

    return sitio;


}


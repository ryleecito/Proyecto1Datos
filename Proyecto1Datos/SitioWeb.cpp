#include "SitioWeb.h"
const size_t MAX_LENGTH = 2048;

SitioWeb::SitioWeb() : url(""), titulo(""), dominio("") {}

SitioWeb::SitioWeb(std::string url, std::string titulo, std::string dominio)
    : url(url), titulo(titulo), dominio(dominio) {
}

SitioWeb::SitioWeb(const SitioWeb& other)
    : url(other.url), titulo(other.titulo), dominio(other.dominio) {}

SitioWeb::~SitioWeb()
{
    std::cout << "Yo me estoy borrando: " << titulo << this <<std::endl ;
}

std::string SitioWeb::getUrl()
{
    return url;
}

std::string SitioWeb::getTitulo()
{
    return titulo;
}

std::string SitioWeb::getDominio()
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

std::string SitioWeb::toString()
{
    std::stringstream s;
    s << "URL: " << url << " Titulo: " << titulo << " Dominio: " << dominio;
    return s.str();
}

void SitioWeb::guardarArchivoSitioWeb(std::ofstream& out)
{
    size_t urlTama =url.size();
    size_t tituloTama = titulo.size();
    size_t dominioTama = dominio.size();

    out.write(reinterpret_cast<const char*>(&urlTama), sizeof(urlTama));
    out.write(url.c_str(), urlTama);

    out.write(reinterpret_cast<const char*>(&tituloTama), sizeof(tituloTama));
    out.write(titulo.c_str(), tituloTama);

    out.write(reinterpret_cast<const char*>(&dominioTama), sizeof(dominioTama));
    out.write(dominio.c_str(), dominioTama);

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
    return new SitioWeb(url, titulo, dominio);
}

void SitioWeb::guardarArchivoSitioWebCSV(std::ofstream& out)
{
    out << url << "," << "\"" << titulo << "\"," << dominio << "\n";
}

SitioWeb* SitioWeb::cargarArchivoSitioWebCSV(std::string& nombre)
{
    std::ifstream in(nombre);
    std::string linea, url_, titulo_, dominio_;

    if (in.is_open()) {
        if (std::getline(in, linea)) {
            std::stringstream ss(linea);
            std::getline(ss, url_, ',');
            std::getline(ss, titulo_, ',');
            std::getline(ss, dominio_, ',');
            return new SitioWeb(url_, titulo_, dominio_);
        }
        in.close();
    }
    else {
        std::cerr << "Error al abrir el archivo: " << nombre << std::endl;
    }
    return nullptr;

}
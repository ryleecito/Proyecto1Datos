#include "PestaniaIncognito.h"

void PestaniaIncognito::guardarArchivoPestania(std::ofstream& out)
{
    return;
}

PestaniaIncognito::PestaniaIncognito() : sitio(nullptr)
{
}

PestaniaIncognito::PestaniaIncognito(SitioWeb* sitioWeb) : sitio(new SitioWeb(*sitioWeb))
{
}

PestaniaIncognito::PestaniaIncognito(const PestaniaIncognito& pest)
{
	this->sitio = new SitioWeb(*pest.sitio);
}

PestaniaIncognito::~PestaniaIncognito()
{
	delete sitio;
}

void PestaniaIncognito::setSitioWeb(SitioWeb* sitioWeb)
{
    	delete sitio;
	this->sitio = new SitioWeb(*sitioWeb);
}

SitioWeb* PestaniaIncognito::getSitioWeb() const
{
    if (sitio) {
		return sitio;
	}
    return nullptr;
}

Historial* PestaniaIncognito::getHistorial() const
{
    return nullptr;
}

std::string PestaniaIncognito::toString() const
{
    std::stringstream s;
    const int width = 40;
    const int contentWidth = width - 4;
    const std::string border(width, '-');

    if (sitio != nullptr) {
        s << "              NAVEGADOR WEB          " << std::endl;
        s << border << std::endl;
        s << "[ " << std::string(contentWidth, ' ') << " ]" << std::endl;
        s << "[ " << "URL: " << sitio->getUrl()
            << std::string(contentWidth - ("URL: " + sitio->getUrl()).length(), ' ') << " ]" << std::endl;
        s << "[ " << "Titulo: " << sitio->getTitulo()
            << std::string(contentWidth - ("Titulo: " + sitio->getTitulo()).length(), ' ') << " ]" << std::endl;
        s << "[ " << "Dominio: " << sitio->getDominio()
            << std::string(contentWidth - ("Dominio: " + sitio->getDominio()).length(), ' ') << " ]" << std::endl;
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

int PestaniaIncognito::sizeHistorial() const
{
	if (sitio) {
		return 1;
	}
	return 0;
	
}

void PestaniaIncognito::agregarPaginaWeb(SitioWeb* sitioWeb)
{
    if (sitio) {
        delete sitio;
        this->sitio =  new SitioWeb (*sitioWeb);
    }

	this->sitio = new SitioWeb(*sitioWeb);
    
}

void PestaniaIncognito::irAtras()
{
	return;
}

void PestaniaIncognito::irAdelante()
{
	return;
}

SitioWeb* PestaniaIncognito::getSitioActual() const
{
	return sitio;
}

void PestaniaIncognito::ajustarTamanoHistorial()
{
	return;
}

bool PestaniaIncognito::limpiarEntradasViejas()
{
	return false;
}

std::string PestaniaIncognito::busquedaPalabraClave(const std::string& palabraClave)
{
	return "";
}

void PestaniaIncognito::moverseAPrimeraCoincidencia()
{
	return;
}

void PestaniaIncognito::setFiltro(const std::string& filtro)
{
	return;
}

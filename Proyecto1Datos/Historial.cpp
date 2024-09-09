#include "Historial.h"

Historial::Historial()
{

}

Historial::~Historial()
{
}

void Historial::navegar(SitioWeb* sitioWeb)
{
    pilaAtras.push(sitioWeb);
    while (!pilaAdelante.empty()) {
        pilaAdelante.pop();
    }
}

void Historial::retroceder()
{
    if (!pilaAtras.empty()) {
        SitioWeb* sitio = pilaAtras.top();
        pilaAtras.pop();
        pilaAdelante.push(sitio);
    }
}

void Historial::avanzar()
{
    if (!pilaAdelante.empty()) {
        SitioWeb* sitio = pilaAdelante.top();
        pilaAdelante.pop();
        pilaAtras.push(sitio);
    }
}

void Historial::limpiarHistorial()
{
    while (!pilaAtras.empty()) {
        pilaAtras.pop();
    }
    while (!pilaAdelante.empty()) {
        pilaAdelante.pop();
    }

}

void Historial::importarHistorial(ifstream& in) {
    limpiarHistorial();

    std::string url, titulo, dominio;
    while (getline(in, url)) {
        if (getline(in, titulo) && getline(in, dominio)) {
            SitioWeb* sitio = new SitioWeb(url, titulo, dominio);
            navegar(sitio);
        }
    }
}

void Historial::exportarHistorial(ofstream& out) {
    std::stack<SitioWeb*> temp = pilaAtras;
    while (!temp.empty()) {
        SitioWeb* sitio = temp.top();
        out << sitio->getUrl() << std::endl;
        out << sitio->getTitulo() << std::endl;
        out << sitio->getDominio() << std::endl;
        temp.pop();
    }
}

stack<SitioWeb*> Historial::getpilaAtras()
{
    return pilaAtras;
}

stack<SitioWeb*> Historial::getpilaAdelante()
{
    return pilaAdelante;
}

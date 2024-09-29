#include "ConfigHistorial.h"


ConfigHistorial* ConfigHistorial::instancia = nullptr;

ConfigHistorial::ConfigHistorial()
{
    maxEntradas = -1;
    tiempoMaximo = -1;  
}

void ConfigHistorial::destruirInstancia()
{
	if (instancia != nullptr)
	{
		delete instancia;
        std::cout << "configuracion borrada." << std::endl;
		instancia = nullptr;
	}

}

ConfigHistorial* ConfigHistorial::getInstancia()
{
    if (!instancia){
		instancia = new ConfigHistorial();
		atexit(&destruirInstancia);
    }
    return instancia;
 
}

ConfigHistorial::ConfigHistorial(int maxEntradas, int tiempoMax)
{
	this->maxEntradas = maxEntradas;
	this->tiempoMaximo = tiempoMax;
}

ConfigHistorial::~ConfigHistorial()
{
}

void ConfigHistorial::setMaxEntradas(int maxEntradas)
{
    this->maxEntradas = maxEntradas;
}

int ConfigHistorial::getMaxEntradas()
{
    return maxEntradas;
}

void ConfigHistorial::setTiempoMaximo(int tiempoMaximo)
{
    this->tiempoMaximo = tiempoMaximo;
}

int ConfigHistorial::getTiempoMaximo()
{
    return tiempoMaximo;
}

void ConfigHistorial::guardarArchivoConfigHistorial(std::ofstream& out)
{
    out.write(reinterpret_cast<const char*>(&maxEntradas), sizeof(maxEntradas));
    out.write(reinterpret_cast<const char*>(&tiempoMaximo), sizeof(tiempoMaximo));  
}

ConfigHistorial* ConfigHistorial::cargarArchivoConfigHistorial(std::ifstream& in)
{
    ConfigHistorial* config = getInstancia();
    in.read(reinterpret_cast<char*>(&config->maxEntradas), sizeof(config->maxEntradas));
    in.read(reinterpret_cast<char*>(&config->tiempoMaximo), sizeof(config->tiempoMaximo));  
    return config;
}
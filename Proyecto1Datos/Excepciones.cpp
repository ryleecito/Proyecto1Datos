#include "Excepciones.h"

ExcepcionGenerica::ExcepcionGenerica(const std::string& msg)noexcept : mensaje(msg) 
{

}

const char* ExcepcionGenerica::what() const noexcept
{
    return mensaje.c_str();
}



#pragma once
#include <iostream>
#include <exception>
#include <string>

class ExcepcionGenerica : public std::exception {
private:
    std::string mensaje;

public:
    // Constructor que permite pasar un mensaje personalizado
    explicit ExcepcionGenerica(const std::string& msg) noexcept : mensaje(msg) {}

    // Sobreescribe la función what() de std::exception para devolver el mensaje
    virtual const char* what() const noexcept override {
        return mensaje.c_str();
    }
};
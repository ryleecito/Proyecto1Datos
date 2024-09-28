#pragma once
#include <iostream>
#include <exception>
#include <string>

class ExcepcionGenerica : public std::exception {
private:
    std::string mensaje;

public:
 
    explicit ExcepcionGenerica(const std::string& msg) noexcept;

    virtual const char* what() const noexcept override;
};
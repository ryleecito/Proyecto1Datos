#pragma once

#include <iostream>
#include <sstream>
using namespace std;

class Excepcion {
public:
    Excepcion() {}
    virtual ~Excepcion() {}
    virtual const char* what() const throw() = 0;
    virtual string toString() = 0;
};

class ExcepcionRango : public Excepcion {
protected:
    int min;
    int max;

public:
    ExcepcionRango(int min, int max) : min(min), max(max) {}
    virtual ~ExcepcionRango() {}
    virtual const char* what() const throw() { return "Excepcion de rango"; }
    virtual string toString() = 0;
};

class ExcepcionMin : public ExcepcionRango {
private:
    int valor;

public:
    ExcepcionMin(int min, int max, int val) : ExcepcionRango(min, max), valor(val) {}
    virtual ~ExcepcionMin() {}
    virtual const char* what() {
        return "Valor por debajo del minimo permitido";
    }
    virtual string toString() {
        stringstream ss;
        ss << "ExcepcionMin: Valor " << valor << " es menor que el minimo permitido " << min;
        return ss.str();
    }
};

class ExcepcionMax : public ExcepcionRango {
private:
    int valor;

public:
    ExcepcionMax(int min, int max, int val) : ExcepcionRango(min, max), valor(val) {}
    virtual ~ExcepcionMax() {}
    virtual const char* what() {
        return "Valor por encima del maximo permitido";
    }
    virtual string toString() {
        stringstream ss;
        ss << "ExcepcionMax: Valor " << valor << " es mayor que el maximo permitido " << max;
        return ss.str();
    }
};

class ExcepcionTipo : public Excepcion {
public:
    ExcepcionTipo() {}
    virtual ~ExcepcionTipo() {}
    virtual const char* what() const throw() { return "Se ha digitado un caracter invalido"; }
    virtual string toString() { return "Se ha digitado un caracter invalido"; }
};
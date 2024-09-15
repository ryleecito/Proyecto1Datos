//#include <iostream>
//#include "Historial.h"
//#include "SitioWeb.h"
//
//int main() {
//    // Crear el historial
//    Historial historial;
//
//    // Crear algunos sitios web
//    SitioWeb* sitio1 = new SitioWeb("https://www.google.com", "Google", "google.com");
//    SitioWeb* sitio2 = new SitioWeb("https://www.youtube.com", "YouTube", "youtube.com");
//    SitioWeb* sitio3 = new SitioWeb("https://www.github.com", "GitHub", "github.com");
//    SitioWeb* sitio4 = new SitioWeb("https://www.stackoverflow.com", "Stack Overflow", "stackoverflow.com");
//
//    // Navegar a los sitios web
//    historial.add(sitio1);
//    historial.add(sitio2);
//    historial.add(sitio3);
//    
//    // Mostrar el sitio actual
//    std::cout << "Sitio actual: " << historial.getSitioActual()->toString() << std::endl;
//
//    // Retroceder en el historial
//    historial.retroceder();
//    std::cout << "Retrocediendo...\nSitio actual: " << historial.getSitioActual()->toString() << std::endl;
//
//    historial.retroceder();
//    std::cout << "Retrocediendo...\nSitio actual: " << historial.getSitioActual()->toString() << std::endl;
//
//    // Avanzar en el historial
//    historial.avanzar();
//    std::cout << "Avanzando...\nSitio actual: " << historial.getSitioActual()->toString() << std::endl;
//
//    // Navegar a un nuevo sitio, esto debe borrar el historial futuro
//    historial.add(sitio4);
//    std::cout << "Navegando a un nuevo sitio...\nSitio actual: " << historial.getSitioActual()->toString() << std::endl;
//
//    // Tratar de avanzar (debería no hacer nada porque estamos en el último sitio)
//    historial.avanzar();
//    std::cout << "Intentando avanzar...\nSitio actual: " << historial.getSitioActual()->toString() << std::endl;
//
//    // Mostrar todo el historial
//    std::cout << "Historial completo:\n";
//    for (SitioWeb* sitio : historial.getHistorial()) {
//        std::cout << sitio->toString() << std::endl;
//    }
//
//    // Limpiar el historial
//    std::cout << "\nLimpiando el historial...\n";
//    historial.limpiarHistorial();
//
//    return 0;
//}
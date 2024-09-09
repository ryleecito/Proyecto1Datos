#include "Controladora.h"

Controladora::Controladora() {
    navegador = new Navegador();
}

Controladora::~Controladora() {
    if (navegador != nullptr) {
        delete navegador;
    }
}

void Controladora::mostrarNavegador() {
    
    /*

      const int width = 40;
      const int contentWidth = width - 4;
      const string border(width, '-');

      string tabTitle = "Google";
      string url = "https://www.google.com";
      string currentSite = "Google";

      system("cls");
      cout << "              NAVEGADOR WEB          " << endl;
      cout << border << endl;
      cout << "[ " << string(contentWidth, ' ') << " ]" << endl;
      cout << "[ " << "Pestana: " << tabTitle << string(contentWidth - ("Pestana: " + tabTitle).length(), ' ') << " ]" << endl;
      cout << "[ " << "URL: " << url << string(contentWidth - ("URL: " + url).length(), ' ') << " ]" << endl;
      cout << "[ " << "Titulo: " << currentSite << string(contentWidth - ("Titulo: " + currentSite).length(), ' ') << " ]" << endl;
      cout << "[ " << string(contentWidth, ' ') << " ]" << endl;
      cout << border << endl;
      cout << endl;*/ //(esto tiene que ir en el tostring de pestania)
    cout << " ESTE ES EL NAVEGADORRRRRRRRRRRRRRRRRRRR" << endl;

}

void Controladora::control0() {
    int opcion = 0;
    do {
            system("cls");
            mostrarNavegador(); // Mostramos el navegador
            opcion = Interfaz::navegadorPrincipal();
            switch (opcion) {
            case 1: // Página anterior
                cout << "Navegando a la página anterior..." << endl;
                break;
            case 2: // Página siguiente
                cout << "Navegando a la página siguiente..." << endl;
                break;
            case 3: // Pestaña anterior
                cout << "Cambiando a la pestaña anterior..." << endl;
                break;
            case 4: // Pestaña siguiente
                cout << "Cambiando a la pestaña siguiente..." << endl;
                break;
            case 0: // Ir al menú del navegador
                return;
            }
        
    } while (opcion != 0); 
}

void Controladora::control1() {
    int opcion = 0;
    do {
        try {
            opcion = Interfaz::menuNavegador(); // Mostramos el menu
            switch (opcion) {
                case 1: // Ir al navegador actual
                    control0();
                    break;
                case 2: // Navegar a un sitio web
                    
                    break;
                case 3: // Agregar un bookmark
                 
                    break;
                case 4: // Importar / Exportar historial
                   
                    break;
                case 5: // Mostrar bookmarks
                  
                    break;
                case 6: // busqueda y filtros
               
                    break;
                case 7: // Activar / desactivar modo incógnito
                 
                    break;
                case 8: // Nueva pestnaia
                   
                    break;
                case 9: // Salir
                    return;
                default:
                    throw ExcepcionTipo(); 
            }
        } catch (ExcepcionTipo& ex) {
            cout << "Error: " << ex.what() << endl;
            system("pause");
        } catch (ExcepcionMin& ex) {
            cout << "Error: " << ex.what() << endl;
            system("pause");
        } catch (ExcepcionMax& ex) {
            cout << "Error: " << ex.what() << endl;
            system("pause");
        } catch (...) {
            cout << "Error desconocido." << endl;
            system("pause");
        }
    } while (opcion != 9);
}
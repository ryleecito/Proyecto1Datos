#include "Controladora.h"

Controladora::Controladora() {
    navegador = new Navegador();
}

Controladora::~Controladora() {
    if (navegador != nullptr) {
        delete navegador;
    }
}


void Controladora::control0() {
    int opcion = 0;
    do {
        try {
            opcion = Interfaz::navegadorPrincipal(navegador);
            switch (opcion) {
                case 1: // Ir al navegador actual
                    break;
                case 2: // agregar a un sitio web
                    
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


// bookmarks
void Controladora::control2()
{
}
// historial importar exportar
void Controladora::control3()
{
}
//mostrar bookmarks
void Controladora::control4()
{
}
// busqueda y filtros
void Controladora::control5()
{
}
// activar desactivar modo incognito
void Controladora::control6()
{
}
// nueva pestaña
void Controladora::control7()
{
}

// pagina anterior
void Controladora::control8()
{
}
// pagina siguiente
void Controladora::control9()
{
}
// pestaña anterior
void Controladora::control10()
{
}
// pestaña siguiente
void Controladora::control11()
{
}

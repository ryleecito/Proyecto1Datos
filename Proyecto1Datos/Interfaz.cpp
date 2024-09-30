
#pragma once
#include "Interfaz.h"



void Interfaz::mostrarNavegador(Navegador* navegador) 
{

    system("cls");

    if (navegador->getModoIncognito()) {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "|        Modo incognito activado        | " << std::endl;
        std::cout << "----------------------------------------" << std::endl << std::endl;
    }
    else {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "|        Modo incognito desactivado     | " << std::endl;
        std::cout << "----------------------------------------" << std::endl << std::endl;
    }

    if (navegador->cantidadPestanias() == 0) {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "|            No hay pestanias           | " << std::endl;
        std::cout << "----------------------------------------" << std::endl << std::endl;
    }
    else {
       
        std::cout << "Pestania " << navegador->posicionDelIndex() + 1 << std::endl;
        std::cout << navegador->mostrarPestaniaActual() << std::endl;

    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "|  Flecha izquierda / pagina anterior   |" << std::endl;
    std::cout << "|  Flecha derecha / pagina siguiente    |" << std::endl;
    std::cout << "|  Flecha arriba / pestania siguiente   |" << std::endl;
    std::cout << "|  Flecha abajo / pestania anterior     |" << std::endl;
    std::cout << "|  Espacio / ir al menu del navegador   |" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "|                 MENU                  | " << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "| 1. Navegar a un sitio web             |" << std::endl;
    std::cout << "| 2. Agregar un bookmark                |" << std::endl;
    std::cout << "| 3. Importar / Exportar Historial      |" << std::endl;
    std::cout << "| 4. Mostrar bookmarks                  |" << std::endl;
    std::cout << "| 5. Busqueda y filtros                 |" << std::endl;
    std::cout << "| 6. Activar / desactivar modo incognito|" << std::endl;
    std::cout << "| 7. Nueva pestania                     |" << std::endl;
    std::cout << "| 8. Configuracion de historial         |" << std::endl;
    std::cout << "| 9. Salir                              |" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Toque tecla para realizar accion: "<<std::endl<<std::endl;

}


int Interfaz::detectarTecla(Navegador* navegador, bool mainMenu)
{

    //Aqui se muestra el menu principal y la funcion donde se detectan las teclas
    //Cabe aclarar que se uso una api de windows para lo mismo y como espera constantemente una tecla
    //se hizo un bucle infinito que solo se rompe cuando detecta una de las teclas especificadas

    // HANDLE es un tipo de dato que representa un manejador, en este caso para la entrada estandar
    // Esto permite intereactuar con la consola con el teclado
    HANDLE consola = GetStdHandle(STD_INPUT_HANDLE);

    //El INPUT_RECORD es una estructura que contiene informacion sobre un evento de entrada, guardamos
    //en un buffer de 128 porque es recomendado para evitar errores si entran muchos inputs a la vez
    INPUT_RECORD bufferDeEventos[128];

    //DWORD basicamente es un tipo de numero muy grande que cuenta la cantidad de eventos leidos en este caso
    //Se usa DWORD ya que para las funciones de la API de windows se usa este tipo de dato
    DWORD eventosLeidos;

    int tecla = 0;

    if (mainMenu) {
        mostrarNavegador(navegador);
    }

    while (true) {


        if (navegador->getSitioActual()) {
            if (navegador->limpiarSitiosViejos() && mainMenu) {//aqui se esta verificando constantemente los sitios viejos
                mostrarNavegador(navegador);//por eso se hizo bool, si se devuelve que si borro un sitio por tiempo se actualiza el navegador
            }
        }
        //Este DWORD es para capturar los eventos de entrada que han OCURRIDO a diferencia 
        DWORD eventosOcurridos = 0;
        if (GetNumberOfConsoleInputEvents(consola, &eventosOcurridos) && eventosOcurridos > 0) {//obtenemos los eventos ocurridos

            if (PeekConsoleInput(consola, bufferDeEventos, 128, &eventosLeidos)) {

                //El peek consel recibe donde ocurren los eventos, el buffer donde se guardan, la cantidad de eventos que se pueden guardar
                //y la cantidad de eventos leidos

                //A diferencia del ReadConsoleInput el peek no limpia/procesa los elementos solo los guarada para examinarlos

                for (DWORD i = 0; i < eventosLeidos; i++) { //ahora recorremos en buffer en busqueda de eventos

                    if (bufferDeEventos[i].EventType == KEY_EVENT && bufferDeEventos[i].Event.KeyEvent.bKeyDown) {

                        //Primero detecttamos que el evento sea de teclado con el event type
                        // y luego que el evento sea de presionar una tecla con el bKeyDown

                        switch (bufferDeEventos[i].Event.KeyEvent.wVirtualKeyCode) {//Examinamos el codigo de la tecla y si cumple con alguna se devueve un valor
                        case VK_LEFT: tecla = 10; break;                            //Que sera procesado en la controladora
                        case VK_RIGHT: tecla = 11; break;
                        case VK_UP: tecla = 12; break;
                        case VK_DOWN: tecla = 13; break;
                        default:

                            //Ahora si no coincide con las teclas de navegacion se examina si es una tecla numerica
                            //Se obtiene el el uChar que es un tipo de dato que almacena un caracter.
                            //luego se obtiene el codigo ascii de ese caracter y se verifica si esta entre el ascii 1 y de 9


                            if (bufferDeEventos[i].Event.KeyEvent.uChar.AsciiChar >= '1' &&
                                bufferDeEventos[i].Event.KeyEvent.uChar.AsciiChar <= '9') {
                                tecla = bufferDeEventos[i].Event.KeyEvent.uChar.AsciiChar - '0'; // si es asi se toma el caracter y se le resta el ascii de 0
                                                                                                 //que devolvera el numero entero correspondiente a la tecla
                            }
                            break;
                        }
                        if (tecla != 0) {
                            FlushConsoleInputBuffer(consola); //Se limpia el buffer de entrada
                            return tecla; //Y se devuelve la tecla
                        }
                    }
                }
            }
        }

    }
}


void Interfaz::agregarPestania(Navegador* navegador )
{
    navegador->agregarPestania();
}

void Interfaz::pestaniaAnterior(Navegador* navegador)
{
    navegador->pestaniaAnterior();
}

void Interfaz::pestaniaSiguiente(Navegador* navegador)
{
    navegador->pestaniaSiguiente();
}

void Interfaz::agregarPaginaWeb(Navegador* navegador)
{
  
    std::string url;
    std::cout << " Ingrese la URL: ";
    std::cin >> url;

    SitioWeb* sitio = navegador->buscarPaginaWeb(url);

    if (!navegador->getPestaniaActual()) {

        agregarPestania(navegador);
    }

    sitio->setTiempoDeIngreso(std::chrono::system_clock::now());
    navegador->agregarPaginaWeb(sitio);
       
    system("pause");
}

void Interfaz::paginaAnterior(Navegador* navegador)
{
    navegador->paginaAnterior();
}

void Interfaz::paginaSiguiente(Navegador* navegador)
{

    navegador->paginaSiguiente();

}

void Interfaz::agregarBookmark(Navegador* navegador)
{
	if (navegador->getModoIncognito()) {
		throw ExcepcionGenerica("No se pueden agregar bookmarks en modo incognito");

	}
    if (!navegador->getSitioActual()) {
        throw ExcepcionGenerica("No hay pagina para hacer bookmark");
    }

    SitioWeb* sitioActual = navegador->getSitioActual();


    std::string tag;
    std::cout << " Ingrese un tag: ";
    std::cin >> tag;
    
    Marcador* marcadorExistente = navegador->buscarMarcadorPorSitio(sitioActual);

    if (marcadorExistente) {
        marcadorExistente->anadirEtiqueta(tag);
    }
    else {
        navegador->agregarMarcador(new Marcador(sitioActual, tag));
    }
    
}

void Interfaz::mostrarBookmarks(Navegador* navegador)
{
    if (navegador->getModoIncognito()) {
        throw ExcepcionGenerica("No se pueden mostrar bookmarks en modo incognito");
    }
    std::cout << navegador->mostrarMarcadoresGuardados();
    system("pause");
}

void Interfaz::cambiarModoIncognito(Navegador* navegador)
{
	navegador->cambiarModoIncognito();
}

void Interfaz::agregarCantidadEntradas(Navegador* navegador)
{

    int opc;
	std::cout << " Ingrese la cantidad de entradas: ";
    std::cin >> opc;
	if (opc <= 0) {
		throw ExcepcionGenerica("La cantidad de entradas no puede ser negativa ni 0");
	}
    if (std::cin.fail()) { 
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw ExcepcionGenerica("Entrada invalida. Debe ingresar un numero entero.");
    }

	navegador->setMaxEntradas(opc);

    system("pause");
}

void Interfaz::agregarCantidadTiempo(Navegador* navegador)
{
    int opc;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << " 5 minutos = 300 segundos" << std::endl;
    std::cout << " 10 minutos = 600 segundos" << std::endl;
    std::cout << " 30 minutos = 1800 segundos  " << std::endl;

    std::cout << "----------------------------------------" << std::endl;
    std::cout << " Ingrese la cantidad de segundos para el timeout del navegador: ";

    std::cin >> opc;

    if (opc < 0) {
        throw ExcepcionGenerica("La cantidad de segundos no puede ser negativa");
    }
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw ExcepcionGenerica("Entrada invalida. Debe ingresar un numero entero.");
    }

	navegador->setTiempoMaximo(opc);
   
    std::cout << " Se ha agregado la cantidad de tiempo a: " << opc << std::endl;
    system("pause");
}


void Interfaz::menuConfiguraciones(Navegador* navegador)
{
    if (navegador->getModoIncognito()) {
        throw ExcepcionGenerica("No se puede configurar en modo incognito");
    }

    system("cls");
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "|         MENU DE CONFIGURACION         | " << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "| 1. Configurar cantidad de entradas    |" << std::endl;
    std::cout << "| 2. Configurar tiempo de entradas      |" << std::endl;
    std::cout << "| 3. Reiniciar configuraciones          |" << std::endl;
    std::cout << "| 4. Regresar                           |" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Toque tecla para realizar accion: " << std::endl << std::endl;
}

void Interfaz::busquedaYFiltros(Navegador* navegador)
{
    if (navegador->getModoIncognito()) {
        throw ExcepcionGenerica("No se pueden hacer busquedas ni filtros en modo incognito");
    }

    system("cls");
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "|       MENU BUSQUEDA Y FILTROS               | " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "| 1. Buscar paginas web por filtro            |" << std::endl;
    std::cout << "| 2. Buscar paginas web                       |" << std::endl;
    std::cout << "| 3. Eliminar filtro anadido                  |" << std::endl;
    std::cout << "| 4. Regresar                                 |" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "Toque tecla para realizar accion: " << std::endl << std::endl;
}

void Interfaz::busquedaPalabraClave(Navegador* navegador)
{

    std::string opc;
    int contador = 1;
    std::cout << " Ingrese la palabra clave para hacer la busqueda:";
    std::cin >> opc;
    std::cout<<navegador->busquedaPalabraClave(opc);
    system("pause");
    
}

void Interfaz::aplicarFiltroNavegador(Navegador* navegador)
{

    std::string opc;
    std::cout << " Ingrese la palabra clave para aplicarle el filtro al navegador:";
    std::cin >> opc;
    navegador->setFiltro(opc);
	system("pause");
}


void Interfaz::menuImportarExportar(Navegador* navegador)
{
    if (navegador->getModoIncognito()) {
        throw ExcepcionGenerica("No se pueden importar/exportar en modo incognito");
    }
    system("cls");
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "| 1. Exportar historial (con sus bookmarks) |" << std::endl;
    std::cout << "| 2. Importar historial (con sus bookmarks) |" << std::endl;
    std::cout << "| 3. Regresar                               |" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Toque tecla para realizar accion: " << std::endl << std::endl;
    
}

Navegador* Interfaz::importarHistorial(Navegador* navegador)
{
    std::string opc;
    std::cout << "Ingrese el nombre de la sesion que quiere importar al navegador: ";
    std::cin >> opc;

    std::ifstream archivo(opc+".bin", std::ios::binary);
    if (!archivo) {
        throw ExcepcionGenerica("Error: No se ha podido abrir el archivo, verifique el nombre de la sesion");
    }

    Navegador* navegadorCargado = Navegador::cargarArchivoNavegador(archivo);

    if (navegadorCargado) {
        std::cout << "Se ha importado el historial con exito." << std::endl;
        system("pause");
    }
    else {
        throw ExcepcionGenerica("Error: No se ha podido importar el historial correctamente.");
    }

    archivo.close();
    return navegadorCargado;  
}

void Interfaz::exportarHistorial(Navegador* navegador)
{

    std::string opc;
    std::cout << "Ingrese el nombre con el que quiere guardar la sesion: ";
    std::cin >> opc;

    std::ofstream archivo(opc+".bin", std::ios::binary);
    if (!archivo) {
        throw ExcepcionGenerica("Error: No se ha podido crear el archivo.");
		system("pause");
    }
    navegador->guardarArchivoNavegador(archivo);
    std::cout << "Se ha exportado el historial con exito." << std::endl;
	system("pause");
    archivo.close(); 
   
}

void Interfaz::eliminarFiltro(Navegador* navegador)
{
	std::cout << " Se ha eliminado el filtro del navegador" << std::endl;
	system("pause");
    navegador->setFiltro("");
}

void Interfaz::quitarConfiguraciones(Navegador* navegador)
{
    navegador->reiniciarConfiguraciones();
}

void Interfaz::mensajeSalida()
{
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "|  GRACIAS POR NAVEGAR CON NOSOTROS :)  | " << std::endl;
    std::cout << "----------------------------------------" << std::endl << std::endl;
}





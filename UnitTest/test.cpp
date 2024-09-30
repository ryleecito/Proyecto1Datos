#include "pch.h"
#include "gtest/gtest.h"
#include "..\Proyecto1Datos\Historial.cpp"
#include "..\Proyecto1Datos\SitioWeb.cpp"
#include "..\Proyecto1Datos\ConfigHistorial.cpp"
#include "..\Proyecto1Datos\Pestania.cpp"
#include "..\Proyecto1Datos\PestaniaIncognito.cpp"
#include "..\Proyecto1Datos\ListaPestanias.cpp"
#include "..\Proyecto1Datos\Navegador.cpp"
#include "..\Proyecto1Datos\Marcador.cpp"
#include "..\Proyecto1Datos\Excepciones.cpp"

//Para configurar irse a propiedades del unit test
//en la parte de c/c++-> preprocesador-> definir _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
// en encabezados precompilados poner NO Utilizar encabezados precompilados


TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

//TEST DE HISTORIAL
TEST(HistorialTest1, AddSite) {
    Historial historial;
    SitioWeb* sitio1 = new SitioWeb("www.google.com", "Google", "dominio");
    historial.add(sitio1);
    EXPECT_EQ(historial.size(), 1);
    EXPECT_EQ(historial.getSitioActual()->getTitulo(), "Google");
}

TEST(HistorialTest, RetrocederYAvanzar) {
    Historial historial;
    SitioWeb* sitio1 = new SitioWeb("www.google.com", "Google", "dominio");
    SitioWeb* sitio2 = new SitioWeb("www.youtube.com", "Youtube", "dominio");

    historial.add(sitio1);
    historial.add(sitio2);

    historial.retroceder();
    EXPECT_EQ(historial.getSitioActual()->getTitulo(), "Google");

    historial.avanzar();
    EXPECT_EQ(historial.getSitioActual()->getTitulo(), "Youtube");
}

TEST(HistorialTest, LimpiarHistorial) {
    Historial historial;
    SitioWeb* sitio1 = new SitioWeb("www.google.com", "Google", "dominio");
    historial.add(sitio1);
    historial.limpiarHistorial();
    EXPECT_EQ(historial.size(), 0);
    EXPECT_EQ(historial.getSitioActual(), nullptr);
}


TEST(HistorialTest, AjustarTamanoHistorial) {
    Historial historial;
    ConfigHistorial* config = config->getInstancia();
    config->setMaxEntradas(1);

    SitioWeb* sitio1 = new SitioWeb("www.google.com", "Google", "dominio");
    SitioWeb* sitio2 = new SitioWeb("www.youtube.com", "Youtube", "dominio");

    historial.add(sitio1);
    historial.add(sitio2);
    historial.ajustarTamanoHistorial();
    EXPECT_EQ(historial.size(), 1);
    EXPECT_EQ(historial.getSitioActual()->getTitulo(), "Youtube"); 

    config->setMaxEntradas(-1);
}

//TEST DE PESTANIA

TEST(PestaniaTest, IrAtrasYAdelante) {
    Historial* historial = new Historial();
    SitioWeb* sitio1 = new SitioWeb("www.google.com", "Google", "dominio");
    SitioWeb* sitio2 = new SitioWeb("www.youtube.com", "Youtube", "dominio");

    historial->add(sitio1);
    historial->add(sitio2);

    Pestania pestania(historial);
    pestania.irAtras(); 
    pestania.irAdelante();

    EXPECT_EQ(pestania.getHistorial()->getSitioActual()->getTitulo(), "Youtube");
}

TEST(PestaniaTest, AgregarPaginaWeb) {
    Historial* h = new Historial();
    Pestania p(h);
    SitioWeb* sitio = new SitioWeb("www.google.com", "Google", "dom");
    p.agregarPaginaWeb(sitio);
    EXPECT_EQ(h->getSitioActual()->getUrl(), sitio->getUrl());
}

TEST(PestaniaTest, AgregarPaginaWebCuandoExiste) {

    PestaniaAbstracta* p = new Pestania();
    SitioWeb* sitio = new SitioWeb("www.google.com", "Google", "dom");
    SitioWeb* sitio1 = new SitioWeb("www.youtube.com", "Youtube", "dom");
    SitioWeb* sitio2 = new SitioWeb("www.Yahoo.com", "Yahoo", "dom");
    SitioWeb* sitio3 = new SitioWeb("www.google.com", "Google", "dom");

    p->agregarPaginaWeb(sitio);
    p->agregarPaginaWeb(sitio1);
    p->agregarPaginaWeb(sitio2);
    p->agregarPaginaWeb(sitio3);

    EXPECT_EQ((int)p->sizeHistorial(), 3);
    EXPECT_EQ((*p->getHistorial()->getHistorial().begin())->getUrl(), "www.youtube.com");
    EXPECT_EQ((*(std::prev(p->getHistorial()->getHistorial().end())))->getUrl(), "www.google.com");
}

//TEST DE LISTAPESTANIAS

TEST(ListPestaniasTest, AddPestania) {
    ListPestanias lista;
    PestaniaAbstracta* pestania1 = new Pestania();
    lista.add(pestania1);

    EXPECT_EQ(lista.size(), 1);
    EXPECT_EQ(lista.getPosicionActualIndex(), 0);
    EXPECT_EQ(lista.getPestaniaActual(), pestania1);
}

TEST(ListPestaniasTest, RetrocederYAvanzar) {
    ListPestanias lista;
    PestaniaAbstracta* pestania1 = new Pestania();
    PestaniaAbstracta* pestania2 = new Pestania();
    lista.add(pestania1);
    lista.add(pestania2);

    lista.retroceder();
    lista.avanzar();     

    EXPECT_EQ(lista.getPestaniaActual(), pestania2);
    EXPECT_EQ(lista.getPosicionActualIndex(), 1);
}

TEST(ListPestaniasTest, LimpiarPestanias) {
    ListPestanias lista;
    PestaniaAbstracta* pestania1 = new Pestania();
    PestaniaAbstracta* pestania2 = new Pestania();
    lista.add(pestania1);
    lista.add(pestania2);

    lista.limpiarPestanias();

    EXPECT_EQ(lista.size(), 0);
    EXPECT_EQ(lista.getPestaniaActual(), nullptr);
    EXPECT_EQ(lista.getPosicionActualIndex(), -1);
}

TEST(ListPestaniasTest, AgregarPaginaWeb) {
    ListPestanias lista;
    PestaniaAbstracta* pestania = new Pestania();
    SitioWeb* sitio = new SitioWeb("www.google.com", "Google", "dominio");
    lista.add(pestania);
    lista.agregarPaginaWeb(sitio);

    EXPECT_EQ(lista.getPestaniaActual()->getHistorial()->getSitioActual()->getUrl(), sitio->getUrl());
}

//TEST NAVEGADOR
TEST(NavegadorTest, CambiarModoIncognito) {
    Navegador navegador;

    EXPECT_FALSE(navegador.getModoIncognito());
    navegador.cambiarModoIncognito();
    EXPECT_TRUE(navegador.getModoIncognito());
    navegador.cambiarModoIncognito();
    EXPECT_FALSE(navegador.getModoIncognito());
}

TEST(NavegadorTest, MoverseEntrePestanias) {
    Navegador navegador;


    navegador.agregarPestania();
    navegador.agregarPestania();
    EXPECT_EQ(navegador.posicionDelIndex(), 1);
    navegador.pestaniaAnterior();
    EXPECT_EQ(navegador.posicionDelIndex(), 0);
    navegador.pestaniaSiguiente();
    EXPECT_EQ(navegador.posicionDelIndex(), 1);
}

TEST(NavegadorTest, AgregarYMostrarMarcadores) {
    Navegador navegador;
    SitioWeb* sitio = new SitioWeb("www.google.com", "Google", "dominio");
    Marcador* marcador = new Marcador(sitio, "buscar");

    int marcadoresInicial = navegador.getMarcadoresGuardados().size();
    navegador.agregarMarcador(marcador);

    EXPECT_EQ(navegador.getMarcadoresGuardados().size(), marcadoresInicial + 1);

    std::string output = navegador.mostrarMarcadoresGuardados();
    EXPECT_NE(output.find("Google"), std::string::npos); 
}

TEST(NavegadorTest, AgregarPaginaWebIncognito) {
    Navegador navegador;
    navegador.cambiarModoIncognito(); 

    ListPestanias* list = new ListPestanias();
    navegador.agregarPestania();

    SitioWeb* sitio = new SitioWeb("www.google.com", "Google", "dom");
    navegador.agregarPaginaWeb(sitio);

    EXPECT_EQ(navegador.getSitioActual()->getUrl(), "www.google.com");
}

TEST(NavegadorTest, AgregarPaginaWeb) {
    Navegador navegador;
    navegador.agregarPestania();

    SitioWeb* sitio = new SitioWeb("www.google.com", "Google", "dom");
    navegador.agregarPaginaWeb(sitio);

    EXPECT_EQ(navegador.getSitioActual()->getUrl(), "www.google.com");
}

TEST(NavegadorTest, BuscarPaginaWebExistente) {
    Navegador navegador;
    SitioWeb* sitio1 = new SitioWeb("www.youtube.com", "Youtube", "dom");
    SitioWeb* sitio2 = new SitioWeb("www.google.com", "Google", "dom");
    SitioWeb* sitio3 = new SitioWeb("www.Yahoo.com", "Yahoo", "dom");
    navegador.getListaSitiosW()->push_back(sitio1);
    navegador.getListaSitiosW()->push_back(sitio2);
    navegador.getListaSitiosW()->push_back(sitio3);

    navegador.agregarPestania();

    navegador.agregarPaginaWeb(sitio1);
    navegador.agregarPaginaWeb(sitio2);
    navegador.agregarPaginaWeb(sitio3);

    const std::string url = "www.google.com";

    SitioWeb* sitioBuscado = navegador.buscarPaginaWeb(url);

    EXPECT_NE(sitioBuscado, nullptr); 
    EXPECT_EQ(sitioBuscado->getUrl(), "www.google.com");  
}

TEST(ArchivosTest, GuardarSitioWeb) {

    SitioWeb* sitioOriginal = new SitioWeb("http://ejemplo.com", "Ejemplo","ejemplo.com");

    std::ofstream out("sitios_test.bin", std::ios::binary);
    ASSERT_TRUE(out.is_open()); 

    sitioOriginal->guardarArchivoSitioWeb(out);
    out.close();

    std::ifstream in("sitios_test.bin", std::ios::binary);
    ASSERT_TRUE(in.is_open());

    SitioWeb* sitioCargado = SitioWeb::cargarArchivoSitioWeb(in);
    in.close();

    ASSERT_NE(sitioCargado, nullptr); 
    EXPECT_EQ(sitioOriginal->getTitulo(), sitioCargado->getTitulo()); 
    EXPECT_EQ(sitioOriginal->getUrl(), sitioCargado->getUrl()); 

    delete sitioOriginal;
    delete sitioCargado;

    std::remove("sitios_test.bin");
}
TEST(ArchivosTest, GuardarYLeerHistorial) {

    Historial historial;

    SitioWeb* sitio1 = new SitioWeb("https://example1.com", "Ejemplo 1", "example1.com");
    SitioWeb* sitio2 = new SitioWeb("https://example2.com", "Ejemplo 2", "example2.com");
    SitioWeb* sitio3 = new SitioWeb("https://example3.com", "Ejemplo 3", "example3.com");

    historial.add(sitio1);
    historial.add(sitio2);
    historial.add(sitio3);

    std::ofstream archivoSalida("historial_test.bin", std::ios::binary);
    ASSERT_TRUE(archivoSalida.is_open());
    historial.guardarArchivoHistorial(archivoSalida);
    archivoSalida.close();


    historial.limpiarHistorial();

    std::ifstream archivoEntrada("historial_test.bin", std::ios::binary);
    ASSERT_TRUE(archivoEntrada.is_open());
    Historial* historialCargado = Historial::cargarArchivoHistorial(archivoEntrada);
    archivoEntrada.close();

    ASSERT_NE(historialCargado, nullptr); 
    ASSERT_EQ(historialCargado->size(), 3);

    SitioWeb* sitioCargado1 = historialCargado->getHistorial().front(); 
    SitioWeb* sitioCargado2 = *(++historialCargado->getHistorial().begin()); 
    SitioWeb* sitioCargado3 = historialCargado->getHistorial().back(); 


    EXPECT_EQ(sitioCargado1->getDominio(), "example1.com");
    EXPECT_EQ(sitioCargado1->getUrl(), "https://example1.com");
    EXPECT_EQ(sitioCargado1->getTitulo(), "Ejemplo 1");

    EXPECT_EQ(sitioCargado2->getDominio(), "example2.com");
    EXPECT_EQ(sitioCargado2->getUrl(), "https://example2.com");
    EXPECT_EQ(sitioCargado2->getTitulo(), "Ejemplo 2");

    EXPECT_EQ(sitioCargado3->getDominio(), "example3.com");
    EXPECT_EQ(sitioCargado3->getUrl(), "https://example3.com");
    EXPECT_EQ(sitioCargado3->getTitulo(), "Ejemplo 3");


    EXPECT_EQ(historialCargado->getUrlActual(), "https://example3.com");
    EXPECT_EQ(historialCargado->getTituloActual(), "Ejemplo 3");
    EXPECT_EQ(historialCargado->getDominioActual(), "example3.com");


    EXPECT_EQ(historialCargado->getUrlActual(), historialCargado->getSitioActual()->getUrl());


    historialCargado->limpiarHistorial();
    delete historialCargado;
}

TEST(ArchivosTest, PestaniaCargar) {

    PestaniaAbstracta* pestania = new Pestania();
    EXPECT_EQ(pestania->sizeHistorial(), 0);


    SitioWeb* sitio1 = new SitioWeb("https://example1.com", "Ejemplo 1", "example1.com");
    pestania->agregarPaginaWeb(sitio1);
    EXPECT_EQ(pestania->sizeHistorial(), 1);
    EXPECT_EQ(pestania->getSitioActual()->getUrl(), "https://example1.com"); 


    SitioWeb* sitio2 = new SitioWeb("https://example2.com", "Ejemplo 2", "example2.com");
    pestania->agregarPaginaWeb(sitio2);
    EXPECT_EQ(pestania->sizeHistorial(), 2); 


    pestania->irAtras();
    EXPECT_EQ(pestania->getSitioActual()->getUrl(), "https://example1.com");


    std::ofstream archivoSalida("pestania_test.bin", std::ios::binary);
    ASSERT_TRUE(archivoSalida.is_open());
    pestania->guardarArchivoPestania(archivoSalida);
    archivoSalida.close();


    delete pestania; 
    pestania = nullptr;

    std::ifstream archivoEntrada("pestania_test.bin", std::ios::binary);
    ASSERT_TRUE(archivoEntrada.is_open());
    pestania = Pestania::cargarArchivoPestania(archivoEntrada);
    archivoEntrada.close();

    ASSERT_NE(pestania, nullptr);
    EXPECT_EQ(pestania->sizeHistorial(), 2);
    EXPECT_EQ(pestania->getSitioActual()->getUrl(), "https://example1.com"); 

    delete pestania;
}
TEST(ArchivosTest, TestGuardarYcargarPestaniasYPaginas) {
    ListPestanias* listaOriginal = new ListPestanias();


    PestaniaAbstracta* pestania1 = new Pestania();
    PestaniaAbstracta* pestania2 = new Pestania();


    SitioWeb* sitio1 = new SitioWeb("https://example1.com", "Ejemplo 1", "example1.com");
    SitioWeb* sitio2 = new SitioWeb("https://example2.com", "Ejemplo 2", "example2.com");

    pestania1->agregarPaginaWeb(sitio1);
    pestania2->agregarPaginaWeb(sitio2);

    listaOriginal->add(pestania1);
    listaOriginal->add(pestania2);


    std::ofstream out("pestanias.dat", std::ios::binary);
    ASSERT_TRUE(out.is_open());
    listaOriginal->guardarArchivoListaPestanias(out);
    out.close();

    ListPestanias* listaCargada = new ListPestanias();
    std::ifstream in("pestanias.dat", std::ios::binary);
    ASSERT_TRUE(in.is_open());  
    listaCargada = ListPestanias::cargarArchivoListaPestanias(in);
    in.close();


    EXPECT_EQ(listaOriginal->size(), listaCargada->size());

    EXPECT_EQ(listaOriginal->getPestaniaActual()->getSitioActual()->getUrl(), listaCargada->getSitioActual()->getUrl());

    delete listaOriginal;
    delete listaCargada;
}














#include "pch.h"
#include "gtest/gtest.h"
#include "..\Proyecto1Datos\Historial.cpp"
#include "..\Proyecto1Datos\SitioWeb.cpp"
#include "..\Proyecto1Datos\ConfigHistorial.cpp"
#include "..\Proyecto1Datos\Pestania.cpp"
#include "..\Proyecto1Datos\ListaPestanias.cpp"
#include "..\Proyecto1Datos\Navegador.cpp"
#include "..\Proyecto1Datos\Marcador.cpp"

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

TEST(HistorialTest, FiltrarPorNombre) {
    Historial historial;
    SitioWeb* sitio1 = new SitioWeb("www.google.com", "Google", "dominio");
    SitioWeb* sitio2 = new SitioWeb("www.youtube.com", "Youtube", "dominio");
    historial.add(sitio1);
    historial.add(sitio2);
    auto filtrados = historial.filtrarPaginasPorNombre("Google");
    EXPECT_EQ(filtrados.size(), 1);
    EXPECT_EQ(filtrados.front()->getTitulo(), "Google");
}

TEST(HistorialTest, AjustarTamanoHistorial) {
    Historial historial;
    ConfigHistorial* config = config->getInstancia();

    SitioWeb* sitio1 = new SitioWeb("www.google.com", "Google", "dominio");
    SitioWeb* sitio2 = new SitioWeb("www.youtube.com", "Youtube", "dominio");

    historial.add(sitio1);
    historial.add(sitio2);
    historial.ajustarTamanoHistorial();
    EXPECT_EQ(historial.size(), 1);
    EXPECT_EQ(historial.getSitioActual()->getTitulo(), "Youtube"); 
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
    EXPECT_EQ(h->getSitioActual(), sitio);
}

//TEST DE LISTAPESTANIAS

TEST(ListPestaniasTest, AddPestania) {
    ListPestanias lista;
    Pestania* pestania1 = new Pestania();
    lista.add(pestania1);

    EXPECT_EQ(lista.size(), 1);
    EXPECT_EQ(lista.getPosicionActualIndex(), 0);
    EXPECT_EQ(lista.getPestaniaActual(), pestania1);
}

TEST(ListPestaniasTest, RetrocederYAvanzar) {
    ListPestanias lista;
    Pestania* pestania1 = new Pestania();
    Pestania* pestania2 = new Pestania();
    lista.add(pestania1);
    lista.add(pestania2);

    lista.retroceder();
    lista.avanzar();     

    EXPECT_EQ(lista.getPestaniaActual(), pestania2);
    EXPECT_EQ(lista.getPosicionActualIndex(), 1);
}

TEST(ListPestaniasTest, LimpiarPestanias) {
    ListPestanias lista;
    Pestania* pestania1 = new Pestania();
    Pestania* pestania2 = new Pestania();
    lista.add(pestania1);
    lista.add(pestania2);

    lista.limpiarPestanias();

    EXPECT_EQ(lista.size(), 0);
    EXPECT_EQ(lista.getPestaniaActual(), nullptr);
    EXPECT_EQ(lista.getPosicionActualIndex(), -1);
}

TEST(ListPestaniasTest, AgregarPaginaWeb) {
    ListPestanias lista;
    Pestania* pestania = new Pestania();
    SitioWeb* sitio = new SitioWeb("www.google.com", "Google", "dominio");
    lista.add(pestania);
    lista.agregarPaginaWeb(sitio);

    EXPECT_EQ(lista.getPestaniaActual()->getHistorial()->getSitioActual(), sitio);
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

TEST(NavegadorTest, AgregarPestania) {
    Navegador navegador;
    Pestania* pestania = new Pestania();
    int pestaniasInicial = navegador.cantidadPestanias();
    navegador.agregarPestania(pestania);
    EXPECT_EQ(navegador.cantidadPestanias(), pestaniasInicial + 1);
}

TEST(NavegadorTest, MoverseEntrePestanias) {
    Navegador navegador;
    Pestania* pestania1 = new Pestania();
    Pestania* pestania2 = new Pestania();

    navegador.agregarPestania(pestania1);
    navegador.agregarPestania(pestania2);
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
    Pestania* pestania = new Pestania();
    navegador.agregarPestania(pestania);

    SitioWeb* sitio = new SitioWeb("www.google.com", "Google", "dom");
    navegador.agregarPaginaWeb(sitio);

    EXPECT_EQ(navegador.getSitioActual()->getUrl(), "www.google.com");
}

TEST(NavegadorTest, AgregarPaginaWeb) {
    Navegador navegador;
    Pestania* pestania = new Pestania();
    navegador.agregarPestania(pestania);

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

    Pestania* pestania = new Pestania();
    navegador.agregarPestania(pestania);

    navegador.agregarPaginaWeb(sitio1);
    navegador.agregarPaginaWeb(sitio2);
    navegador.agregarPaginaWeb(sitio3);

    const std::string url = "www.google.com";

    SitioWeb* sitioBuscado = navegador.buscarPaginaWeb(url);

    EXPECT_NE(sitioBuscado, nullptr); 
    EXPECT_EQ(sitioBuscado->getUrl(), "www.google.com");  
}













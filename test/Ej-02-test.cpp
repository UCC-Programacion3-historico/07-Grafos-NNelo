#include "gtest/gtest.h"
#include "../Ej-02/GrafoEnlazado.h"

using namespace std;

GrafoEnlazado<string, int> *G;

TEST(test_Ej02, test) {
    EXPECT_EQ(true, true);
}

TEST(test_Ej02, esVacio){
    G = new GrafoEnlazado<string, int>();
    EXPECT_TRUE(G->esVacio());
}

TEST(test_Ej02, agregaderecho){
    G->nodo_agregar("cuatro");
    G->nodo_agregar("cinco");
    G->nodo_agregar("seis");
    G->arco_agregar("cinco", "cuatro", 10);
    G->arco_agregar("cinco", "seis", 11);
    G->arco_agregar("seis", "cuatro", 4);
    G->nodo_agregar("siete");
    EXPECT_FALSE(G->esVacio());
}

TEST(test_Ej02, adyacentes){
    EXPECT_TRUE(G->adyacentes("cinco", "cuatro"));
    EXPECT_TRUE(G->adyacentes("cinco", "seis"));
    EXPECT_TRUE(G->adyacentes("seis", "cuatro"));
    EXPECT_FALSE(G->adyacentes("cuatro", "cinco"));
    EXPECT_FALSE(G->adyacentes("cuatro", "seis"));
    EXPECT_FALSE(G->adyacentes("seis", "cinco"));

    string arr[] = {"cuatro", "cinco", "seis"};
    for (int i = 0; i < 3 ; ++i)
        EXPECT_FALSE(G->adyacentes("siete", arr[i]));
}

TEST(test_Ej02, vecinos){
    Lista<string> *v = G->vecinos("cinco");
    EXPECT_EQ(2, v->getTamanio());
    EXPECT_TRUE("cuatro" == v->getDato(0) || "cuatro" == v->getDato(1));
    EXPECT_TRUE("seis" == v->getDato(0) || "seis" == v->getDato(1));
    EXPECT_FALSE("ocho" == v->getDato(0) || "ocho" == v->getDato(1));
}

TEST(test_Ej02, getPesos){
    EXPECT_EQ(10, G->arco_get_val("cinco", "cuatro"));
    EXPECT_ANY_THROW(G->arco_get_val("cuatro", "cinco"));
}
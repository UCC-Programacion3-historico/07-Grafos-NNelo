#ifndef GRAFOENLAZADO_H
#define GRAFOENLAZADO_H

#include "Lista.h"

//Implemente una clase Grafo utilizando nodos enlazados

typedef struct Arco;

template<class T, class P>      // P peso de los arcos
typedef
struct Vertice {
    T dato;
    Lista<Arco> tablaAdyacentes;
};                      // vertice es la info de nodoVertice, tiene dato y puntero a lista multienlazada

template<class T, class P>
typedef
struct Arco {                        //tabla Adyacentes
    P peso;
    Nodo<Vertice> *ptrVert;      // imp: apunta a un NODO que es del tipo vertice
};                         // arco es la info de nodoArco, contiene dato P y puntero a Vertice

/**
 * Clase que implementa la representación de un grafo por listas multienlazadas
 * @tparam T cualquier tipo de dato para valores de los nodos o vertices
 * @tparam P cualquier tipo de dato para valores de los arcos o aristas
 */

template<class T, class P>
class GrafoEnlazado {
private:
    Lista<Vertice> tablaDirectorio;  // Lista multienlazada que contiene los vertices

    Nodo<Arco> *devuelveArco(Nodo<Vertice> *, Nodo<Vertice> *);

public:
    GrafoEnlazado();

    // Metodos de Nodos

    void nodo_agregar(T);

    void nodo_remover(T);

    void nodo_set_val(T, T);

    //int nodo_get_val();


    // Metodos de Arcos

    void arco_agregar(T, T, P);

    void arco_remover(T, T);

    void arco_set_val(T, T, P);

    P arco_get_val(T, T);


    bool adyacentes(T, T);

    Lista<T> *vecinos(T);

    bool esVacio();
};

template<class T, class P>
GrafoEnlazado<T, P>::GrafoEnlazado() {
    // hace algo? xdxdxd
}

template<class T, class P>
void GrafoEnlazado<T, P>::nodo_agregar(T val) {
    tablaDirectorio.insertarUltimo({val, nullptr});
}

template<class T, class P>
void GrafoEnlazado<T, P>::nodo_remover(T val) {
    tablaDirectorio.remover(val);
}

/**
 * Metodo que modifica el valor de un vertice
 * @param valor anterior por el cual se busca al nodo, nuevo valor
 */
template<class T, class P>
void GrafoEnlazado<T, P>::nodo_set_val(T valAnt, T valNuevo) {
    Nodo<Vertice> *aux = tablaDirectorio.delataNodo(valAnt);        // calculo que aca se tira la excp
    Vertice tmp = {aux->getDato().dato, aux->getDato().tablaAdyacentes};
    aux->setDato({valNuevo, tmp.tablaAdyacentes});
}

//template<class T>
//int GrafoEnlazado<T>::nodo_get_val(int n2) {
//    return 0;
//}

template<class T, class P>
void GrafoEnlazado<T, P>::arco_agregar(T datoV1, T datoV2, P peso) {
//    if (!tablaDirectorio.pertenece(datoV1))
//        throw 1;
//    if (!tablaDirectorio.pertenece(datoV2))
//        throw 2;
//    //deberia hacerlo con delataNodo

    // controlar que el arco no exista de antes

    Nodo<Vertice> *V1 = tablaDirectorio.delataNodo(datoV1); //tira excp?
    Nodo<Vertice> *V2 = tablaDirectorio.delataNodo(datoV2);

    if (this->devuelveArco(V1, V2) != nullptr)
        throw -48;

    V1->getDato().tablaAdyacentes.insertarUltimo({peso, V2});
}

/**
 * Metodo que devuelve null si no existe arco entre de un vertice a otro, o bien devuelve
 * el NODO arco que representa el arco
 * @param sale vertice con arco externo
 * @param entra vertice con arco interno
 */
template<class T, class P>
Nodo<Arco> *GrafoEnlazado<T, P>::devuelveArco(Nodo<Vertice> *sale, Nodo<Vertice> *entra) {
    Nodo<Arco> *aux = sale->getDato().tablaAdyacentes.getInicio();

    while (nullptr != aux) {
        if (aux->getDato().ptrVert == entra)
            return aux;
        aux->getNext();
    }
    return nullptr;
}

template<class T, class P>
void GrafoEnlazado<T, P>::arco_remover(T datoV1, T datoV2) {
    Nodo<Vertice> *V1 = tablaDirectorio.delataNodo(datoV1);

    Nodo<Arco> *tmp = this->devuelveArco(V1, tablaDirectorio.delataNodo(datoV2));
    if (tmp == nullptr)
        throw -4;

    V1->getDato().tablaAdyacentes.remover(tmp->getDato());
    //estaria recorriendo dos veces la lista, en devuelve arco y remueve
}

template<class T, class P>
void GrafoEnlazado<T, P>::arco_set_val(T datoV1, T datoV2, P nuevo) {
    Nodo<Vertice> *V1 = tablaDirectorio.delataNodo(datoV1);
    Nodo<Vertice> *V2 = tablaDirectorio.delataNodo(datoV2);

    Nodo<Arco> *tmp = this->devuelveArco(V1, V2);
    if (tmp == nullptr)
        throw -4;

    tmp->setDato({nuevo, tmp->getDato().ptrVert});
}

template<class T, class P>
P GrafoEnlazado<T, P>::arco_get_val(T datoV1, T datoV2) {
    Nodo<Vertice> *V1 = tablaDirectorio.delataNodo(datoV1);
    Nodo<Vertice> *V2 = tablaDirectorio.delataNodo(datoV2);

    Nodo<Arco> *tmp = this->devuelveArco(V1, V2);
    if (tmp == nullptr)
        throw -4;

    return tmp->getDato().peso;
}

template<class T, class P>
bool GrafoEnlazado<T, P>::adyacentes(T datoV1, T datoV2) {
    // puede ser catastrófico
    return (this->devuelveArco(tablaDirectorio.delataNodo(datoV1), tablaDirectorio.delataNodo(datoV2)) != nullptr);
}

// IMPORTANTE: se debe liberar la memoria generada en este metodo
template<class T, class P>
Lista<T> *GrafoEnlazado<T, P>::vecinos(T valorV) {
    Nodo<Arco> *auxArcos = tablaDirectorio.delataNodo(valorV)->getDato().tablaAdyacentes.getInicio();
    Lista<T> *R = new Lista<T>();

    while (nullptr != auxArcos) {
        R->insertarUltimo(auxArcos->getDato().ptrVert->getDato());
        auxArcos = auxArcos->getNext();
    }

    return R;
}

template<class T, class P>
bool GrafoEnlazado<T, P>::esVacio() {
    return tablaDirectorio.esVacia();
}

#endif //GRAFOENLAZADO_H

/*
             . --- .
           /        \
          |  O  _  O |
          |  ./   \. |
          /  `-._.-'  \
        .' /         \ `.
    .-~.-~/           \~-.~-.
.-~ ~    |             |    ~ ~-.
`- .     |             |     . -'
     ~ - |             | - ~
         \             /
       ___\           /___
       ~;_  >- . . -<  _;~
          `'         `'
 */
#ifndef GRAFOENLAZADO_H
#define GRAFOENLAZADO_H

#include "Lista.h"
#include "Vertice.h"
#include "Arco.h"

//Implemente una clase Grafo utilizando nodos enlazados

/**
 * Clase que implementa la representación de un grafo por listas multienlazadas
 * @tparam T cualquier tipo de dato para valores de los nodos o vertices
 * @tparam P cualquier tipo de dato para valores de los arcos o aristas
 */

template<class T, class P>
class GrafoEnlazado {
private:
    Lista<Vertice<T, P>> tablaDirectorio;  // Lista multienlazada que contiene los vertices

    Nodo<Arco<T,P>> *devuelveArco(Nodo<Vertice<T,P>> *, Nodo<Vertice<T,P>> *);

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
    Nodo<Vertice<T,P>> *aux = tablaDirectorio.delataNodo(valAnt);        // calculo que aca se tira la excp
    Vertice<T,P> tmp = {aux->getDato().dato, aux->getDato().tablaAdyacentes};
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

    Nodo<Vertice<T,P>> *V1 = tablaDirectorio.delataNodo(datoV1); //tira excp?
    Nodo<Vertice<T,P>> *V2 = tablaDirectorio.delataNodo(datoV2);

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
Nodo<Arco<T,P>> *GrafoEnlazado<T, P>::devuelveArco(Nodo<Vertice<T,P>> *sale, Nodo<Vertice<T,P>> *entra) {
    Nodo<Arco<T,P>> *aux = sale->getDato().tablaAdyacentes.getInicio();

    while (nullptr != aux) {
        if (aux->getDato().ptrVert == entra)
            return aux;
        aux->getNext();
    }
    return nullptr;
}

template<class T, class P>
void GrafoEnlazado<T, P>::arco_remover(T datoV1, T datoV2) {
    Nodo<Vertice<T,P>> *V1 = tablaDirectorio.delataNodo(datoV1);

    Nodo<Arco<T,P>> *tmp = this->devuelveArco(V1, tablaDirectorio.delataNodo(datoV2));
    if (tmp == nullptr)
        throw -4;

    V1->getDato().tablaAdyacentes.remover(tmp->getDato());
    //estaria recorriendo dos veces la lista, en devuelve arco y remueve
}

template<class T, class P>
void GrafoEnlazado<T, P>::arco_set_val(T datoV1, T datoV2, P nuevo) {
    Nodo<Vertice<T,P>> *V1 = tablaDirectorio.delataNodo(datoV1);
    Nodo<Vertice<T,P>> *V2 = tablaDirectorio.delataNodo(datoV2);

    Nodo<Arco<T,P>> *tmp = this->devuelveArco(V1, V2);
    if (tmp == nullptr)
        throw -4;

    tmp->setDato({nuevo, tmp->getDato().ptrVert});
}

template<class T, class P>
P GrafoEnlazado<T, P>::arco_get_val(T datoV1, T datoV2) {
    Nodo<Vertice<T,P>> *V1 = tablaDirectorio.delataNodo(datoV1);
    Nodo<Vertice<T,P>> *V2 = tablaDirectorio.delataNodo(datoV2);

    Nodo<Arco<T,P>> *tmp = this->devuelveArco(V1, V2);
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
    Nodo<Arco<T,P>> *auxArcos = tablaDirectorio.delataNodo(valorV)->getDato().tablaAdyacentes.getInicio();
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
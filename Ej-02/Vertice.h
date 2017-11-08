//
// Created by nelon on 31/10/2017.
//

#ifndef INC_07_GRAFOS_VERTICE_H
#define INC_07_GRAFOS_VERTICE_H

#include "Lista.h"
#include "Arco.h"

template<class T, class P>
class Arco;

template<class T, class P>
class Vertice {
public:
    T dato;
    Lista<Arco<T, P>> tablaAdyacentes;

};

#endif //INC_07_GRAFOS_VERTICE_H
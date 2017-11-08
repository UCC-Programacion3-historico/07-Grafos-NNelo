//
// Created by nelon on 31/10/2017.
//

#ifndef INC_07_GRAFOS_ARCO_H
#define INC_07_GRAFOS_ARCO_H

#include "Vertice.h"

template<class T, class P>
class Vertice;

template<class T, class P>
class Arco {
public:
    P peso;
    Nodo<Vertice<T, P>> *ptrVert;
};

#endif //INC_07_GRAFOS_ARCO_H

//
// Created by nelon on 31/10/2017.
//

#ifndef INC_07_GRAFOS_ARCO_H
#define INC_07_GRAFOS_ARCO_H

#include "Vertice.h"

template<class T, class P>
class Arco {
public:
    typedef class Vertice;
    P peso;
    Nodo<Vertice> *ptrVert;
};

#endif //INC_07_GRAFOS_ARCO_H

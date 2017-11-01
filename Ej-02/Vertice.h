//
// Created by nelon on 31/10/2017.
//

#ifndef INC_07_GRAFOS_VERTICE_H
#define INC_07_GRAFOS_VERTICE_H

#include "Lista.h"
#include "Arco.h"

template<class T, class P>
class Vertice {
public:
    typedef class Arco;
    T dato;
    Lista<Arco> tablaAdyacentes;

};

#endif //INC_07_GRAFOS_VERTICE_H
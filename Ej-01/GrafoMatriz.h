#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H


template<class T>
class GrafoMatriz {
private:
    int **valoresArco;
    T **valoresNodo;            //es arreglo de punteros
    bool **existeArco;
    int size;

    bool inRange(int n) {
        return (n >= 0 && n < size);        //to do tirar throws aca   305
    }

public:
    GrafoMatriz(int size);

    ~GrafoMatriz();

    // Metodos de Nodos

    void nodo_agregar(int n, T val);

    void nodo_remover(int n);

    void nodo_set_val(int n, T val);

    T nodo_get_val(int n2);


    // Metodos de Arcos

    void arco_agregar(int n1, int n2, int val);     // los valores podrian tener valor template K

    void arco_remover(int n1, int n2);

    void arco_set_val(int n1, int n2, int val);

    int arco_get_val(int n1, int n2);


    bool adyacentes(int n1, int n2);

    bool *vecinos(int n);

    bool esVacio();
};

template<class T>
GrafoMatriz<T>::GrafoMatriz(int size) {
    this->size = size;
    valoresNodo = new T *[size];
    valoresArco = new int *[size];
    existeArco = new bool *[size];
    for (int i = 0; i < size; ++i) {
        valoresNodo[i] = NULL;
        valoresArco[i] = new int[size];
        existeArco[i] = new bool[size];
        for (int j = 0; j < size; ++j) {
            existeArco[i][j] = false;
        }
    }
}

template<class T>
void GrafoMatriz<T>::nodo_agregar(int n, T val) {
    if (valoresNodo[n] == NULL && inRange(n)) {
        valoresNodo[n] = new T;          //depende del objeto T
        *valoresNodo[n] = val;           //valoresNodo[n] = new T(val) si soporta const por copia
    } else
        throw 303;
}

template<class T>
void GrafoMatriz<T>::nodo_remover(int n) {
    if (valoresNodo[n] != NULL && inRange(n)) {
        for (int i = 0; i < size; ++i) {
            existeArco[i][n] = false;
            existeArco[n][i] = false;
        }
        delete valoresNodo[n];
        valoresNodo[n] = NULL;
    }
}

template<class T>
void GrafoMatriz<T>::nodo_set_val(int n, T val) {
    if (valoresNodo[n] == NULL && !inRange(n))
        throw 321;

    *valoresNodo[n] = val;
}

template<class T>
T GrafoMatriz<T>::nodo_get_val(int n) {
    if (valoresNodo[n] == NULL && !inRange(n))
        throw 321;

    return *valoresNodo[n];
}

template<class T>
void GrafoMatriz<T>::arco_agregar(int n1, int n2, int val) {
    if (valoresNodo[n1] == NULL || !inRange(n1))
        throw 1;
    if (valoresNodo[n2] == NULL || !inRange(n2))
        throw 2;
    if (existeArco[n1][n2])
        throw 3;

    existeArco[n1][n2] = true;
    valoresArco[n1][n2] = val;
}

template<class T>
void GrafoMatriz<T>::arco_remover(int n1, int n2) {
    if (existeArco[n1][n2] && inRange(n1) && inRange(n2)) {
        existeArco[n1][n2] = false;
    } else
        throw 404;
}

template<class T>
void GrafoMatriz<T>::arco_set_val(int n1, int n2, int val) {
    if (existeArco[n1][n2] && inRange(n1) && inRange(n2)) {
        valoresArco[n1][n2] = val;
    } else
        throw 404;
}

template<class T>
int GrafoMatriz<T>::arco_get_val(int n1, int n2) {
    if (existeArco[n1][n2]) {
        return valoresArco[n1][n2];
    }
    throw 404;
}

template<class T>
bool GrafoMatriz<T>::adyacentes(int n1, int n2) {   //conexion directa
    return (existeArco[n1][n2] || existeArco[n2][n1]);
}

// esta funcion devuelve un puntero, debe liberarse memoria en main
template<class T>
bool *GrafoMatriz<T>::vecinos(int n) {
    bool *resultado = new bool[size];
    for (int i = 0; i < size; ++i) {
        resultado[i] = (existeArco[n][i] || existeArco[i][n]);
    }
    return resultado;
    //return nullptr;
}

template<class T>
bool GrafoMatriz<T>::esVacio() {
    for (int i = 0; i < size; ++i)
        if (valoresNodo[i] != nullptr)
            return false;
    return true;
}

template<class T>
GrafoMatriz<T>::~GrafoMatriz() {
    for (int i = 0; i < size; ++i) {
        if (valoresArco[i] != nullptr)
            delete valoresNodo[i];
    }
}

#endif //GRAFOMATRIZ_H
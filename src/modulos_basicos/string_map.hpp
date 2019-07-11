#include "string_map.h"

using namespace algo2;

template <typename T>
string_map<T>::string_map(){
    _raiz = NULL;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    borradoRecursivo(_raiz);
    _raiz = copiadoRecursivo(d._raiz);
    return *this;
}

template <typename T>
string_map<T>::~string_map(){
    borradoRecursivo(_raiz);
}

template <typename T>
void string_map<T>::Definir(const string &clave, T valor) {
    // Si la raiz no existe la creo
    if (_raiz == NULL) {
        _raiz = new Nodo(_claves);
    }

    // Recorro
    Nodo* actual = _raiz;
    for (char c : clave) {
        actual = obtenerOCrearSiguiente(actual, c);
    }

    // Si no tiene definicion la creo, agrego la clave al conjunto de claves
    // y apunto el iterador del nodo a la clave
    if (actual->definicion == NULL) {
        actual->definicion = new T(valor);
        actual->itClave = _claves.insert(clave).first;
    } else {
        delete actual->definicion;
        actual->definicion = new T(valor);
    }
};

template <typename T>
bool string_map<T>::Definido(const string &clave) const{
    if (_raiz == NULL) {
        return false;
    }
    Nodo* actual = _raiz;
    int i = 0;
    while (i < clave.size() and actual->siguientes[int(clave[i])] != NULL) {
        actual = actual->siguientes[int(clave[i])];
        i++;
    }
    if (i == clave.size() and actual->definicion != NULL){
        return true;
    } else {
        return false;
    }
};

template <typename T>
const T& string_map<T>::Significado(const string &clave) const{
    Nodo* actual = _raiz;
    for (char c : clave) {
        actual = actual->siguientes[int(c)];
    }
    return *(actual->definicion);
};

template <typename T>
T& string_map<T>::Significado(const string &clave) {
    Nodo* actual = _raiz;
    for (char c : clave) {
        actual = actual->siguientes[int(c)];
    }
    return *(actual->definicion);
};

template <typename T>
const set<string>& string_map<T>::Claves() const {
    return _claves;
};

template <typename T>
void string_map<T>::Borrar(const string& clave) {
    Nodo* actual = _raiz;
    Nodo* ultimoRelevante = NULL;
    int indiceArreglar;
    Nodo* borrarDesde = _raiz;

    // Busco la clave
    for (char c : clave) {
        if (nodoRelevante(actual)) {
            // Si el nodo es relevante, lo guardo y tengo que borrar desde el siguiente a el.
            // Tambien guardo indice del puntero que voy a tener que arreglar dsp de borrar
            ultimoRelevante = actual;
            indiceArreglar = int(c);
            actual = actual->siguientes[int(c)];
            borrarDesde = actual;
        } else {
            // Si no es relevante, sigo avanzando.
            actual = actual->siguientes[int(c)];
        }
    }
    // Si el nodo actual, que es el que quiero borrar, tiene hijos entonces borro su definicion
    // borro la clave y apunto el iterador al final.
    if (tieneHijos(actual)) {
        delete actual->definicion;
        actual->definicion = NULL;
        _claves.erase(actual->itClave);
        actual->itClave = _claves.end();
    } else {
        // Si no, borro desde el ultimo no relevante
        borradoRecursivo(borrarDesde);
        // Arreglo el puntero del ultimo relevante si existe, y sino existe es que borre desde la raiz
        if (ultimoRelevante) {
            ultimoRelevante->siguientes[indiceArreglar] = NULL;
        } else {
            _raiz = NULL;
        }
    }
}
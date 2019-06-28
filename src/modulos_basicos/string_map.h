#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>
#include <vector>
#include <set>

using namespace std;

namespace algo2 { 

template<typename T>
class string_map {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    string_map();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    string_map(const string_map<T>& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map& operator=(const string_map& d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    /**
    DEFINIR
     * Define un nuevo par clave/valor
     */

    void Definir(const string &clave, T valor);

    /**
    DEFINIDO
     * Devuelve True si y solo si la clave esta definida
     */

    bool Definido(const string &clave) const;

    /**
    SIGNIFICADO
     * Devuelve una referencia inmutable o mutable al significado.
     * PRE: La clave está definida.
     */

    const T& Significado(const string &clave) const;
    T& Significado(const string &clave);

    /**
    * KEYS
    * Devuelve el conjunto de claves por referencia inmutable.
    **/

    const set<string>& Claves() const;

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    **/
    void Borrar(const string& clave);

private:

    struct Nodo {
        vector<Nodo*> siguientes;
        T* definicion;
        set<string>::iterator itClave;

        Nodo(set<string>& c) : siguientes(256, NULL), definicion(NULL), itClave(c.end()) {};
//        Nodo(T* def) : siguientes(256, NULL), definicion(def) {};
    };

    Nodo* _raiz;
    set<string> _claves;

    Nodo* copiadoRecursivo(Nodo* n) {
        // COPIAR CLAVES AL CONJUNTO

        // Si n existe
        if (n != NULL){
            // Creo un nuevo nodo
            Nodo* nuevo = new Nodo(_claves);
            // Copio la definicion si tiene, agrego la clave al conjunto de claves
            // y apunto el iterador del nodo a la clave
            if (n->definicion != NULL){
                nuevo->definicion = new T(*(n->definicion));
                nuevo->itClave = _claves.insert(n->itClave);
            }
            //Copio recursivamente los siguientes
            for (int i = 0; i < 256; ++i) {
                if (n->siguientes[i] != NULL){
                    nuevo->siguientes[i] = copiadoRecursivo(n->siguientes[i]);
                }
            }
            // Retorno
            return nuevo;
        } else {
            return NULL;
        }
    };

    Nodo* obtenerOCrearSiguiente(Nodo* n, char c) {
        if (n->siguientes[int(c)] == NULL) {
            n->siguientes[int(c)] = new Nodo(_claves);
        }
        return n->siguientes[int(c)];
    };

    void borradoRecursivo(Nodo* n) {
        if(n) {
            // Borro la definicion y su clave del conjunto _claves
            borradoRecursivoSiguientes(n->siguientes);
            delete n->definicion;
            if(n->itClave != _claves.end()){
                _claves.erase(n->itClave);
            }
            delete n;
        }
    };

    void borradoRecursivoSiguientes(vector<Nodo*> s) {
        for (Nodo* n : s) {
            if (n) {
                borradoRecursivo(n);
            }
        }
    };

    bool nodoRelevante(const Nodo* n) const {
        unsigned int hijos = 0;
        if (n->definicion){
            return true;
        }
        for (int i = 0; i < 256; ++i) {
            if (n->siguientes[i] != NULL) {
                hijos++;
            }
        }
        return hijos > 1;
    };

    bool tieneHijos(const Nodo* n) const {
        unsigned int hijos = 0;
        for (int i = 0; i < 256; ++i) {
            if (n->siguientes[i] != NULL) {
                hijos++;
            }
        }
        return hijos > 0;
    }
};

}

#include "string_map.hpp"

#endif // STRING_MAP_H_

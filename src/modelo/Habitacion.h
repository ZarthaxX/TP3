#ifndef INC_2019_C1_TP3_HABITACION_H
#define INC_2019_C1_TP3_HABITACION_H

#include <iostream>
#include <set>
#include <vector>
#include "TiposJuego.h"
#include "../modulos_basicos/linear_set.h"

using namespace std;


class Habitacion {
public:
    Habitacion(unsigned int tam);

    Habitacion(unsigned int tam,set<Pos> obs);

    Habitacion(const Habitacion& h);

    ~Habitacion();

    void agregarJugadores(const vector<Pos>& jug);

    void agregarFantasmas(const vector<Pos>& fan);

    void agregarObstaculos(const vector<Pos>& obs);

    bool ocupado(Pos pos) const;

    const linear_set<Pos>& posDisparadasFantasma() const;

    bool estaVivo(bool jug,Pos pos) const;

    Pos adyacente(Pos pos,Dir dir) const;

    void disparar(bool jug, Pos pos, Dir dir);

    void mover(bool jug, Pos pos, Dir dir);

    bool esMovValido(Pos pos,Dir dir) const;

    void resetear();

    unsigned int tam() const;

    bool operator==(const Habitacion&) const;

    void debug();
private:
    struct Celda{
        bool obstaculo;
        int jugadores;
        int fantasmas;
        bool disparada;
        Celda():obstaculo(false),jugadores(0),fantasmas(0),disparada(false){};
        Celda(bool obs,int jug,int fan,bool dis):obstaculo(obs),jugadores(jug),fantasmas(fan),disparada(dis){};
        bool operator==(const Celda& celda) const{
            return obstaculo == celda.obstaculo && jugadores == celda.jugadores && fantasmas == celda.fantasmas && disparada == celda.disparada;
        }
        void resetear(){
            jugadores = 0;
            fantasmas = 0;
            disparada = false;
        }
    };
    Celda** tablero;
    int tamano;
    linear_set<Pos> pos_disparadas;

    bool iEsPosValida(Pos pos) const;


};


Habitacion string_to_hab(std::istream& is);
Habitacion string_to_hab(string s);

#endif

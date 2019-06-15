#ifndef INC_2019_C1_TP3_HABITACION_H
#define INC_2019_C1_TP3_HABITACION_H

#include <iostream>
#include <set>
#include <vector>
#include "TiposJuego.h"
#include "modulos_basicos/linear_set.h"

using namespace std;


class Habitacion {
public:
    Habitacion(unsigned int tam);

    ~Habitacion();

    void agregarJugadores(vector<Pos> jug);

    void agregarFantasmas(vector<Pos> fan);

    void agregarObstaculos(vector<Pos> obs);

    bool esObstaculo(Pos pos);

    const linear_set<Pos>& posDisparadasFantasma();

    bool estaVivo(bool jug,Pos pos);

    Pos adyacente(Pos pos,Dir dir);

    void disparar(bool jug, Pos pos, Dir dir);

    void mover(bool jug, Pos pos, Dir dir);

    bool esMovValido(Pos pos,Dir dir);

    void resetear();

    unsigned int tam() const;

    bool operator==(const Habitacion&) const;

private:
  struct Celda{
      bool obstaculo;
      int jugadores;
      int fantasmas;
      bool disparada;
      Celda():obstaculo(false),jugadores(0),fantasmas(0),disparada(false){};
      void resetear(){
          jugadores = 0;
          fantasmas = 0;
          disparada = false;
      }
  };
  Celda** tablero;
  int tamano;
  linear_set<Pos> pos_disparadas;

  bool iEsPosValida(Pos pos);


};


Habitacion string_to_hab(std::istream& is);
Habitacion string_to_hab(string s);

#endif

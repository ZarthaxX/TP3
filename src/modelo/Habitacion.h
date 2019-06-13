#ifndef INC_2019_C1_TP3_HABITACION_H
#define INC_2019_C1_TP3_HABITACION_H

#include <iostream>
#include <set>
#include <vector>
#include "TiposJuego.h"

using namespace std;


class Habitacion {
public:
    Habitacion(unsigned int tam, set<Pos> ocupadas);

    unsigned int tam() const;

    bool ocupado(Pos) const;

    bool operator==(const Habitacion&) const;

	//Funciones propias nuestras
	void agregarJugadores(const vector<Pos>& jugadores);
	void agregarFantasmas(const vector<Pos>& fantasmas);
	const set<Pos>& posDisparadasFantasma() const;
	bool estaVivo(bool jug, Pos pos) const;
	Pos adyacente(Pos pos, Dir dir) const;
	void disparar(bool jug, Pos pos, Dir dir);
	void mover(bool jug, Pos pos, Dir dir);
	bool esMovValido(Pos pos, Dir dir) const;
	void resetear();
	bool iEsPosValida(Pos pos) const;
private:
	void agregarObstaculos(const set<Pos>& obstaculos);

	//Estructura

};


Habitacion string_to_hab(std::istream& is);
Habitacion string_to_hab(string s);

#endif

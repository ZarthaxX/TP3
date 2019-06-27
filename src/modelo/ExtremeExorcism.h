#ifndef EXTREME_EXORCISM_H
#define EXTREME_EXORCISM_H

#include "Contexto.h"
#include "Habitacion.h"
#include "TiposJuego.h"
#include "modulos_basicos/linear_map.h"
#include <list>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <tuple>

using namespace std;

class ExtremeExorcism {
public:
    //nuevoJuego
    ExtremeExorcism(Habitacion h, set<Jugador> jugadores, PosYDir f_init,
                    list<Accion> acciones_fantasma, Contexto *ctx);

    //pasar
    void pasar();

    //step
    void ejecutarAccion(Jugador j, Accion a);

    //jugadoresVivos
    list<pair<Jugador, PosYDir>> posicionJugadores() const;

    //fantasmasVivos
    list<PosYDir> posicionFantasmas() const;

    //fantasmaEspecial
    PosYDir posicionEspecial() const;

    //fantasmasQueDispararon
    list<PosYDir> disparosFantasmas() const;

    //posPorDisparosEnRonda
    set<Pos> posicionesDisparadas() const;

    //estaVivo?
    bool jugadorVivo(Jugador j) const;

    //habitacion
    const Habitacion &habitacion() const;

    // ???
    PosYDir posicionJugador(Jugador j) const;

    //jugadores
    const set<Jugador> &jugadores() const;

    //fantasmas
    const list<Fantasma> &fantasmas() const;

    //Agregada por nosotros
    const list<Evento> &acciones(string jug) const;

private:

// Estructura
    struct dataJ
    {
		dataJ(string n, Pos p, Dir d, bool v, list<Evento>* a, list<tuple<string, Pos, Dir>>::iterator j) :
			nombre(n), pos(p), dir(d), vivo(v), accionesJ(a), jugadorObs(j) {}
        string nombre;
        Pos pos;
        Dir dir;
        bool vivo;
        list<Evento> *accionesJ;
        list<tuple<string, Pos, Dir>>::iterator jugadorObs;
    };

    struct dataF {
		dataF(int i, Pos p, Dir d, list<list<Evento>>::iterator aa, list<list<Evento>>::iterator ai, list<list<Evento>>::iterator af) :
			id(i), pos(p), dir(d), accionActual(aa), accionInicial(ai), accionFinal(af) {}
        int id;
        Pos pos;
        Dir dir;
        list<list<Evento>>::iterator accionActual;
        list<list<Evento>>::iterator accionInicial;
        list<list<Evento>>::iterator accionFinal;
    };

	void setearMapa();

	void siguienteRonda(dataJ* jugador);

	static list<Evento> inversa(const list<Evento> &acciones);

	static Evento invertir(const Evento &evento);

	Dir direccion(Accion accion);

	Contexto* ctx;

	Habitacion _habitacion;
	map<string, dataJ*>jugadoresPorNombre;
	list<dataJ*> jugadoresV;
	vector<dataJ> _jugadores;
	list<dataF*> fantasmasV;
	list<dataF>_fantasmas;
	list<Fantasma> accionesF;
	vector<list<Evento>>accionesJ;
	list<tuple<string, Pos, Dir>>jugadoresVivosObs;
	list<tuple<Pos, Dir>>fantasmasVivosObs;
};

#endif

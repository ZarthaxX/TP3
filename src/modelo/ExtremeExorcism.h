#ifndef EXTREME_EXORCISM_H
#define EXTREME_EXORCISM_H

#include "Contexto.h"
#include "Habitacion.h"
#include "TiposJuego.h"
#include "modulos_basicos/linear_map.h"
#include "modulos_basicos/string_map.h"
#include <list>
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
    
    //auxiliar para ejecutar pasar y ejecutar accion
    void accionarDemasJugadoresYFantasmas(bool pasarJug, Jugador nombreJ);
	
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
    const set<Jugador> &jugadores() ;

    //fantasmas
    const list<Fantasma> &fantasmas() const;

    //Agregada por nosotros
    const list<Evento> &acciones(string jug) const;

    void debug() const;
private:

// Estructura
    struct dataJ
    {
		dataJ(string n, Pos p, Dir d, bool v, vector<list<Evento>>::iterator a, list<pair<string,PosYDir>>::iterator j) :
			nombre(n), pos(p), dir(d), vivo(v), accionesJ(a), jugadorObs(j) {}
        string nombre;
        Pos pos;
        Dir dir;
        bool vivo;
		vector<list<Evento>>::iterator accionesJ;
        list<pair<string, PosYDir>>::iterator jugadorObs;
    };

    struct dataF {
		dataF(int i, Pos p, Dir d, list<Evento>::iterator aa, list<Evento>::iterator ai, list<Evento>::iterator af) :
			id(i), pos(p), dir(d), accionActual(aa), accionInicial(ai), accionFinal(af) {}
        int id;
        Pos pos;
        Dir dir;
        list<Evento>::iterator accionActual;
        list<Evento>::iterator accionInicial;
        list<Evento>::iterator accionFinal;
    };

	void setearMapa();

	void siguienteRonda(vector<dataJ>::iterator jugador);

	static list<Evento> inversa(const list<Evento> &acciones);

	static Evento invertir(const Evento &evento);

	Dir direccion(Accion accion);

	set<Jugador>jugadores_set;//Remover despues de implementar el trie
	Contexto* ctx;

	Habitacion _habitacion;
	string_map<vector<dataJ>::iterator>jugadoresPorNombre;
	list<vector<dataJ>::iterator> jugadoresV;
	vector<dataJ> _jugadores;
	list<list<dataF>::iterator> fantasmasV;
	list<dataF>_fantasmas;
	list<Fantasma> accionesF;
	vector<list<Evento>>accionesJ;
	list<pair<string, PosYDir>>jugadoresVivosObs;
	list<PosYDir>fantasmasVivosObs;
};

#endif

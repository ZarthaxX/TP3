#ifndef EXTREME_EXORCISM_H
#define EXTREME_EXORCISM_H

#include "Contexto.h"
#include "Habitacion.h"
#include "TiposJuego.h"
#include "modulos_basicos/string_map.h"
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

  PosYDir posicionJugador(Jugador j) const;
  //jugadores
  const set<Jugador> &jugadores() const;
  //fantasmas
  const list<Fantasma> &fantasmas() const;

  //Agregada por nosotros
  const list<Evento> &acciones(string jug) const;
private:
  // Completar
	
// Estructura
	/*< nombre , pos , dir , vivo , accionesJ , jugadorObs >*/
	using dataJ = tuple
	<
		string,
		Pos,
		Dir,
		bool,
		list<Evento>*,
		list<tuple<string, Pos, Dir>>::iterator
	>;
	/*< id , pos , dir , accionActual , accionInicial , accionFinal >*/
	using dataF = tuple
	<
		int,
		Pos,
		Dir,
		list<list<Evento>>::iterator,
		list<list<Evento>>::iterator,
		list<list<Evento>>::iterator
	>;

	Habitacion habitacion;
	map<string, dataJ*>jugadoresPorNombre;
	list<dataJ*> jugadoresV;
	vector<dataJ> jugadores;
	list<dataF*> fantasmasV;
	list<dataF>fantasmas;
	list<list<Evento>> accionesF;
	vector<lista<Evento>>accionesJ;
	list<tuple<string, Pos, Dir>>jugadoresVivosObs;
	list<tuple<Pos, Dir>>fantasmasVivosObs;
};

#endif

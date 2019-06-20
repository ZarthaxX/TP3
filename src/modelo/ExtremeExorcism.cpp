#include "ExtremeExorcism.h"

// Completar

ExtremeExorcism::ExtremeExorcism(Habitacion h, set<Jugador> jugadores, PosYDir f_init, list<Accion> acciones_fantasma, Contexto * ctx) : 
	_habitacion(h),
	_jugadores(vector<dataJ>()),
	_fantasmas(vector<dataF>()),
	jugadoresVivosObs(vector<tuple<string,Pos,Dir>>()),
	fantasmasVivosObs(vector<tuple<Pos, Dir>>()),
	jugadoresPorNombre(map<string,dataJ*>()),
	accionesF(list<Fantasma>()),
	accionesJ(list<list<Evento>>()),
	jugadoresV(list<dataJ*>()),
	fantasmasV(list<dataF*>()),
{	
	//Adaptar a lo que nos pasan, lista de accion a lista de evento
	accionesF.push_back({Evento(Pos(),Dir(),false),Evento(Pos(),Dir(),false),Evento(Pos(),Dir(),false)});
	_fantasmas.push_back(
		dataF(
			0,
			accionesF[0][0].pos,
			accionesF[0][0].dir,
			next(accionesF[0].begin()),
			accionesF[0].begin(),
			prev(accionesF[0].end())
		)
	);

	fantasmasVivosObs.push_back({ _fantasmas[0].pos,_fantasmas[0].dir });

	fantasmasV.push_back(&_fantasmas[0]);

	map<Jugador,PosYDir> pos_dir = ctx->localizar_jugadores(jugadores,accionesF,h);
	for (Jugador j : jugadores) {
		jugadoresVivosObs.push_back(
			{
				j,
				pos_dir[j].pos,
				pos_dir[j].dir 
			}
		);
		accionesJ.push_back(list<Evento>());
		_jugadores.push_back(
			dataJ(
				j,
				pos_dir[j].pos,
				pos_dir[j].dir,
				true,
				&accionesJ.back(),
				prev(jugadoresVivosObs.end())
			)
		);
		jugadoresV.push_back(&_jugadores.back());
		jugadoresPorNombre[j] = &_jugadores.back();
	}

	setearMapa();
}

void ExtremeExorcism::pasar()
{
}

void ExtremeExorcism::ejecutarAccion(Jugador j, Accion a)
{
}

list<pair<Jugador, PosYDir>> ExtremeExorcism::posicionJugadores() const
{
	return list<pair<Jugador, PosYDir>>();
}

list<PosYDir> ExtremeExorcism::posicionFantasmas() const
{
	return list<PosYDir>();
}

PosYDir ExtremeExorcism::posicionEspecial() const
{
	return PosYDir(Pos(),Dir());
}

list<PosYDir> ExtremeExorcism::disparosFantasmas() const
{
	return list<PosYDir>();
}

set<Pos> ExtremeExorcism::posicionesDisparadas() const
{
	return set<Pos>();
}

bool ExtremeExorcism::jugadorVivo(Jugador j) const
{
	return false;
}

const Habitacion & ExtremeExorcism::habitacion() const
{
	return _habitacion;
}

PosYDir ExtremeExorcism::posicionJugador(Jugador j) const
{
	return PosYDir(Pos(),Dir());
}

const set<Jugador>& ExtremeExorcism::jugadores() const
{
    set<Jugador> v;
    for(auto it = jugadoresPorNombre.begin(); it != jugadoresPorNombre.end(); ++it) {
        v.insert(it->first);
    }
	return v;
}

const list<Fantasma>& ExtremeExorcism::fantasmas() const
{
	return accionesF;
}

const list<Evento>& ExtremeExorcism::acciones(string jug) const
{
	return *jugadoresPorNombre.at(jug)->accionesJ;
}

void ExtremeExorcism::setearMapa() {
	_habitacion.resetear();

	vector<Pos> posJugadores;
	for (auto itJugadores = _jugadores.begin(); itJugadores != _jugadores.end(); itJugadores++) {
		posJugadores.push_back(itJugadores->pos);
	}

	vector<Pos> posFantasmas;
	for (auto itFantasmas = _fantasmas.begin(); itFantasmas != _fantasmas.end(); itFantasmas++) {
		posFantasmas.push_back(itFantasmas->pos);
	}

	_habitacion.agregarFantasmas(posFantasmas);
	_habitacion.agregarJugadores(posJugadores);
}

list<Evento> ExtremeExorcism::inversa(const list<Evento>& acciones)
{
	return list<Evento>();
}

Evento ExtremeExorcism::invertir(const Evento & evento)
{
	return Evento(Pos(),Dir(),false);
}

#include "ExtremeExorcism.h"

// Completar

ExtremeExorcism::ExtremeExorcism(Habitacion h, set<Jugador> jugadores, PosYDir f_init, list<Accion> acciones_fantasma, Contexto * ctx) : _habitacion(h)
{
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

list<Evento> ExtremeExorcism::inversa(const list<Evento>& acciones)
{
	return list<Evento>();
}

Evento ExtremeExorcism::invertir(const Evento & evento)
{
	return Evento(Pos(),Dir(),false);
}

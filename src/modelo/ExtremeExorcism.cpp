#include "ExtremeExorcism.h"

// Completar

ExtremeExorcism::ExtremeExorcism(Habitacion h, set<Jugador> jugadores, PosYDir f_init, list<Accion> acciones_fantasma, Contexto * ctx)
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
	return PosYDir();
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
	// TODO: insert return statement here
}

PosYDir ExtremeExorcism::posicionJugador(Jugador j) const
{
	return PosYDir();
}

const set<Jugador>& ExtremeExorcism::jugadores() const
{
	// TODO: insert return statement here
}

const list<Fantasma>& ExtremeExorcism::fantasmas() const
{
	// TODO: insert return statement here
}

const list<Evento>& ExtremeExorcism::acciones(string jug) const
{
	// TODO: insert return statement here
}

list<Evento> ExtremeExorcism::inversa(const list<Evento>& acciones)
{
	return list<Evento>();
}

Evento ExtremeExorcism::invertir(const Evento & evento)
{
	return Evento();
}

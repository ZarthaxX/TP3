#include "ExtremeExorcism.h"

// Completar

int ExtremeExorcism::direccion(Accion acccion) {

	if (accion == MARRIBA)
			return ARRIBA;
	if (accion == MABAJO)
		return ABAJO;
	if (accion == MIZQUIERDA)
		return IZQUIERDA;
	if (accion == MDERECHA)
		return DERECHA;
}

ExtremeExorcism::ExtremeExorcism(Habitacion h, set<Jugador> jugadores, PosYDir f_init, list<Accion> acciones_fantasma, Contexto * ctx) :
	_habitacion(h),
	_jugadores(vector<dataJ>()),
	_fantasmas(vector<dataF>()),
	jugadoresVivosObs(vector<tuple<string, Pos, Dir>>()),
	fantasmasVivosObs(vector<tuple<Pos, Dir>>()),
	jugadoresPorNombre(map<string, dataJ*>()),
	accionesF(list<Fantasma>()),
	accionesJ(list<list<Evento>>()),
	jugadoresV(list<dataJ*>()),
	fantasmasV(list<dataF*>()),
{
	this->ctx = ctx;

//Adaptar a lo que nos pasan, lista de accion a lista de evento
	accionesF.push_back({Evento(Pos(),Dir(),false),Evento(Pos(),Dir(),false),Evento(Pos(),Dir(),false)});
	PosYDir fantasma_actual = f_init;
	accionesF.push_back({ Evento(f_init.pos,f_init.dir,false) });

	for (Accion accion : acciones_fantasma){
		if (accion == DISPARAR) {//Dispara
			accionesF[0].push_back(Evento(fantasma_actual.pos,fantasma_actual.dir,true));
		}
		else if (accion == ESPERAR) //Espera
			accionesF[0].push_back(Evento(fantasma_actual.pos, fantasma_actual.dir, false));
		}
		else {//Se mueve
			if (h.esMovValido(fantasma_actual.pos, direccion(accion))) {
				fantasma_actual.pos = h.adyacente(fantasma_actual.pos, direccion(accion));
			}
			fantasma_actual.dir = direccion(accion);
			accionesF[0].push_back(Evento(fantasma_actual.pos, fantasma_actual.dir, false));
		}
	}

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

void ExtremeExorcism::siguienteRonda(dataJ* punteroJugador) {
	list<Evento> accionesFantasma = *(punteroJugador->accionesJ);
	int i = 5;
	while (i > 0) {
		accionesFantasma.push_back(Evento(punteroJugador->pos, punteroJugador->dir, false));
		i -= 1;
	}
	list<Evento> accionesInvertidas = inversa(*(punteroJugador->accionesJ));
	auto itAccionInv = accionesInvertidas.begin();
	while (itAccionInv != accionesInvertidas.end()) {
		accionesFantasma.push_back(*itAccionInv);
		itAccionInv++;
	}
	int i = 5;
	while (i > 0) {
		accionesFantasma.push_back(
			Evento(
				(*punteroJugador->accionesJ->begin())->pos,
				(*punteroJugador->accionesJ->begin())->dir,
				false
			)
		);
		i -= 1;
	}
	auto itFantasmas = fantasmas.begin();
	accionesF.push_back(accionesFantasma);
	fantasmas.push_back(
		dataF(
			fantasmas.size(),
			punteroJugador->pos,
			punteroJugador->dir,
			prev(accionesF.end())->begin(),
			prev(accionesF.end())->begin(),
			prev(prev(accionesF.end())->end())
		)
	);

	auto itAccionesJ = acccionesJ.begin();

	while (itAccionesJ != accionesJ.end()) {
		*itAccionesJ = list<Evento>();
		itAccionesJ++;
	}

	auto itFan = _fantasmas.begin();
	fantasmasVivosObs = list<tuple<Pos, Dir>>();

	while (itFan != fantasmas.end()) {
		itFan->accionActual = itFan->accionInicial;
		itFan->pos = itFan->accionActual->pos;
		itFan->pos = itFan->accionActual->dir;
		itFan->accionActual++;
		fantasmasV.push_back(&(*itFan));
		fantasmasVivosObs.push_back({ itFan->pos,itFan->dir });
		itFan++;
	}

	map<Jugador, PosYDir> pos_dir = ctx->localizar_jugadores(jugadores, accionesF, h);
	auto itJug = _jugadores.begin();
	jugadoresVivosObs = list<tuple<string, Pos, Dir>>();

	while (itJug != _jugadores.end()) {
		itJug->vivo = true;
		itJug->pos = pos_dir[itJug->nombre].pos;
		itJug->dir = pos_dir[itJug->nombre].dir;
		jugadoresV.push_back(&(*itJug));
		jugadoresVivosObs.push_back({ itJug->nombre,itJug->pos,itJug->dir });
		itJug->jugadorObs = prev(jugadoresVivosObs.end());
		itJug++;
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

#include "ExtremeExorcism.h"

// Completar

Dir ExtremeExorcism::direccion(Accion accion) {

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
	_fantasmas(list<dataF>()),
	jugadoresVivosObs(list<pair<string, PosYDir>>()),
	fantasmasVivosObs(list<PosYDir>()),
	jugadoresPorNombre(map<string, dataJ*>()),
	accionesF(list<Fantasma>()),
	accionesJ(vector<list<Evento>>()),
	jugadoresV(list<dataJ*>()),
	fantasmasV(list<dataF*>())
{
	this->ctx = ctx;

	PosYDir fantasma_actual = f_init;
	accionesF.push_back({ Evento(f_init.pos,f_init.dir,false) });

	for (Accion accion : acciones_fantasma){
		if (accion == DISPARAR) {//Dispara
			accionesF.front().push_back(Evento(fantasma_actual.pos,fantasma_actual.dir,true));
		}
		else if (accion == ESPERAR){ //Espera
			accionesF.front().push_back(Evento(fantasma_actual.pos, fantasma_actual.dir, false));
		}
		else {//Se mueve
			if (h.esMovValido(fantasma_actual.pos, direccion(accion))) {
				fantasma_actual.pos = h.adyacente(fantasma_actual.pos, direccion(accion));
			}
			fantasma_actual.dir = direccion(accion);
			accionesF.front().push_back(Evento(fantasma_actual.pos, fantasma_actual.dir, false));
		}
	}

    list<Evento> accionesInvertidas = inversa(accionesF.front());

    int i = 5;
    while (i > 0) {
        accionesF.front().push_back(Evento(accionesF.front().back().pos, accionesF.front().back().dir, false));
        i -= 1;
    }

    auto itAccionInv = accionesInvertidas.begin();
    while (itAccionInv != accionesInvertidas.end()) {
        accionesF.front().push_back(*itAccionInv);
        itAccionInv++;
    }
    i = 5;
    while (i > 0) {
        accionesF.front().push_back(Evento(f_init.pos,f_init.dir,false));
        i -= 1;
    }

	_fantasmas.push_back(
		dataF(
			0,
			accionesF.front().front().pos,
			accionesF.front().front().dir,
			next(accionesF.front().begin()),
			accionesF.front().begin(),
			accionesF.front().end()
		)
	);

	fantasmasVivosObs.push_back({ _fantasmas.front().pos,_fantasmas.front().dir });

	fantasmasV.push_back(&_fantasmas.front());

	map<Jugador,PosYDir> pos_dir = ctx->localizar_jugadores(jugadores,accionesF,h);
	for (Jugador j : jugadores) {
		jugadoresVivosObs.push_back(
			{
				j,
				PosYDir(pos_dir[j].pos,
				pos_dir[j].dir)
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
	i = 5;
	while (i > 0) {
		accionesFantasma.push_back(
			Evento(
				punteroJugador->accionesJ->begin()->pos,
				punteroJugador->accionesJ->begin()->dir,
				false
			)
		);
		i -= 1;
	}
	auto itFantasmas = _fantasmas.begin();
	accionesF.push_back(accionesFantasma);
	_fantasmas.push_back(
		dataF(
			_fantasmas.size(),
			punteroJugador->pos,
			punteroJugador->dir,
			prev(accionesF.end())->begin(),
			prev(accionesF.end())->begin(),
			prev(prev(accionesF.end())->end())
		)
	);

	auto itAccionesJ = accionesJ.begin();

	while (itAccionesJ != accionesJ.end()) {
		*itAccionesJ = list<Evento>();
		itAccionesJ++;
	}

	auto itFan = _fantasmas.begin();
	fantasmasVivosObs = list<PosYDir>();

	while (itFan != _fantasmas.end()) {
		itFan->accionActual = itFan->accionInicial;
		itFan->pos = itFan->accionActual->pos;
		itFan->dir = itFan->accionActual->dir;
		itFan->accionActual++;
		fantasmasV.push_back(&(*itFan));
		fantasmasVivosObs.push_back({ itFan->pos,itFan->dir });
		itFan++;
	}

	set<Jugador> set_jugadores;
	for(auto it = jugadoresPorNombre.begin(); it != jugadoresPorNombre.end(); ++it) {
		set_jugadores.insert(it->first);
	}
	map<Jugador, PosYDir> pos_dir = ctx->localizar_jugadores(set_jugadores, accionesF, _habitacion);
	auto itJug = _jugadores.begin();
	jugadoresVivosObs = list<pair<string, PosYDir>>();

	while (itJug != _jugadores.end()) {
		itJug->vivo = true;
		itJug->pos = pos_dir[itJug->nombre].pos;
		itJug->dir = pos_dir[itJug->nombre].dir;
		jugadoresV.push_back(&(*itJug));
		jugadoresVivosObs.push_back({ itJug->nombre,PosYDir(itJug->pos,itJug->dir)});
		itJug->jugadorObs = prev(jugadoresVivosObs.end());
		itJug++;
	}
	setearMapa();
}
void ExtremeExorcism::pasar() {
	accionarDemasJugadoresYFantasmas(true, "");
}
void ExtremeExorcism::accionarDemasJugadoresYFantasmas(bool pasarJug, Jugador nombreJ){
	for (auto p : jugadoresV){
		if(p->nombre != nombreJ || pasarJug == true){
			p->accionesJ->push_back(Evento(p->pos,p->dir,false));

		}
	}

	fantasmasVivosObs.clear();
	for(auto punteroF : fantasmasV){
	    if(punteroF->accionActual == punteroF->accionFinal){ //chequear que haga lo que tiene que hacer

	        punteroF->accionActual = punteroF->accionInicial;
	    }
	    Evento a = *(punteroF->accionActual);

	    (punteroF->accionActual)++; // avanzo a la siguiente accion

        if(a.pos != punteroF->pos){

            _habitacion.mover(false, punteroF->pos, a.dir);

        }else if (a.dispara){

            _habitacion.disparar(false, a.pos, a.dir);
        }

        punteroF->pos = a.pos;
        punteroF->dir = a.dir;
        fantasmasVivosObs.push_back(PosYDir(punteroF->pos,punteroF->dir));

	}

	auto itJugV = jugadoresV.begin();

	while(itJugV != jugadoresV.end()){
	    if(!_habitacion.estaVivo(true, (*itJugV)->pos)){
            (*itJugV)->vivo = false;
            auto copia = itJugV;
            itJugV++;
            jugadoresVivosObs.erase((*copia)->jugadorObs);
            jugadoresV.erase(copia);
	    }else{
            (*((*itJugV)->jugadorObs)).second.dir=(*itJugV) -> dir ; // accedo a la tercera posicion de la tupla para cambiar su direccion en jugadores Observable
            (*((*itJugV)->jugadorObs)).second.pos=(*itJugV) -> pos ; // accedo a la segunda posicion de la tupla para cambiar su posicion en jugadores vivos Observables
	    }
	}


}
void ExtremeExorcism::ejecutarAccion(Jugador j, Accion a) {
    dataJ* punteroJ = jugadoresPorNombre[j]; //significado(jugadoresPorNombre, j)
    if(a == MABAJO || a== MARRIBA || a== MDERECHA || a==MIZQUIERDA) {

        if (_habitacion.esMovValido(punteroJ->pos, direccion(a))) {
            _habitacion.mover(true, punteroJ->pos, direccion(a));
            punteroJ->pos = _habitacion.adyacente(punteroJ->pos, direccion(a));
            punteroJ->dir = direccion(a);
            (punteroJ->accionesJ)->push_back(Evento(punteroJ->pos, punteroJ->dir, false));
        } else {
            punteroJ->dir = direccion(a);
            (punteroJ->accionesJ)->push_back(Evento(punteroJ->pos, punteroJ->dir, false));

        }


    } else{
        if(a==DISPARAR){
            _habitacion.disparar(true, punteroJ-> pos, punteroJ->dir);
            list<dataF*>::iterator itFanV = fantasmasV.begin();
            while(itFanV != fantasmasV.end()){
                if(_habitacion.estaVivo(false, (*itFanV)->pos)){
                    if((*itFanV)->id == _fantasmas.size()-1){
                        siguienteRonda(punteroJ);
                        return;
                    }
                    list<dataF*>::iterator copia = itFanV;
                    itFanV++;
                    fantasmasV.erase(copia);

                }
            }
            (punteroJ->accionesJ)->push_back(Evento(punteroJ->pos,punteroJ->dir,true));

        }else{
            (punteroJ->accionesJ)->push_back(Evento(punteroJ->pos,punteroJ->dir, false));
        }
    }
    accionarDemasJugadoresYFantasmas(false, punteroJ->nombre);

}

list<pair<Jugador, PosYDir>> ExtremeExorcism::posicionJugadores() const
{
    return jugadoresVivosObs;
}

list<PosYDir> ExtremeExorcism::posicionFantasmas() const
{
    return fantasmasVivosObs;
}

PosYDir ExtremeExorcism::posicionEspecial() const
{
	return fantasmasVivosObs.back();
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
	return jugadoresPorNombre.at(j)->vivo;
}

const Habitacion & ExtremeExorcism::habitacion() const
{
	return _habitacion;
}

PosYDir ExtremeExorcism::posicionJugador(Jugador j) const
{
	return PosYDir(Pos(),Dir());
}

const set<Jugador>& ExtremeExorcism::jugadores()
{
    jugadores_set.clear();
    for(auto it = jugadoresPorNombre.begin(); it != jugadoresPorNombre.end(); ++it) {
        jugadores_set.insert(it->first);
    }
	return jugadores_set;
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


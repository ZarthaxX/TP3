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
	jugadoresPorNombre(string_map<vector<dataJ>::iterator>()),
	accionesF(list<Fantasma>()),
	accionesJ(vector<list<Evento>>()),
	jugadoresV(list<vector<dataJ>::iterator>()),
	fantasmasV(list<list<dataF>::iterator>())
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
        accionesF.front().push_back(accionesF.front().back());
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

	fantasmasV.push_back(_fantasmas.begin());

	map<Jugador,PosYDir> pos_dir = ctx->localizar_jugadores(jugadores,accionesF,h);

	for (Jugador j : jugadores) {
		jugadoresVivosObs.push_back(
			{
				j,
				PosYDir(pos_dir[j].pos,
				pos_dir[j].dir)
			}
		);
		accionesJ.push_back({Evento(pos_dir[j].pos, pos_dir[j].dir, false)});
		_jugadores.emplace_back(
			dataJ(
				j,
				pos_dir[j].pos,
				pos_dir[j].dir,
				true,
				vector<list<Evento>>::iterator(),//prev(accionesJ.end()),
				list<pair<string, PosYDir>>::iterator()//prev(jugadoresVivosObs.end())
			)
		);
	}

	auto it2 = accionesJ.begin();
	auto it3 = jugadoresVivosObs.begin();

	for(auto it = _jugadores.begin();it != _jugadores.end();it++,it2++,it3++){

		jugadoresV.push_back(it);
		jugadoresPorNombre.Definir(it->nombre, it);
		it->accionesJ = it2;
		it->jugadorObs = it3;
	}

	setearMapa();
}

void ExtremeExorcism::siguienteRonda(vector<dataJ>::iterator punteroJugador) {
	fantasmasV.clear();
	jugadoresV.clear();
	list<Evento> accionesFantasma = *punteroJugador->accionesJ;
	int i = 5;
	while (i > 0) {
		accionesFantasma.push_back(Evento(punteroJugador->pos, punteroJugador->dir, false));
		i -= 1;
	}
	list<Evento> accionesInvertidas = inversa(*(punteroJugador->accionesJ));
	accionesInvertidas.pop_back(); // Saca la ultima accion que representa la posicion inicial
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
	accionesF.push_back(accionesFantasma);
	_fantasmas.push_back(
		dataF(
			_fantasmas.size(),
            (*punteroJugador->accionesJ).front().pos,
            (*punteroJugador->accionesJ).front().dir,
            accionesF.back().begin(),
            accionesF.back().begin(),
            accionesF.back().end()
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
		fantasmasV.push_back(itFan);
		fantasmasVivosObs.push_back({ itFan->pos,itFan->dir });
		itFan++;
	}

	map<Jugador, PosYDir> pos_dir = ctx->localizar_jugadores(jugadoresPorNombre.Claves(), accionesF, _habitacion);
	auto itJug = _jugadores.begin();
	jugadoresVivosObs = list<pair<string, PosYDir>>();

	while (itJug != _jugadores.end()) {
		itJug->vivo = true;
		itJug->pos = pos_dir[itJug->nombre].pos;
		itJug->dir = pos_dir[itJug->nombre].dir;
		jugadoresV.push_back(itJug);
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
            jugadoresVivosObs.erase((*itJugV)->jugadorObs);
            itJugV = jugadoresV.erase(itJugV);
	    }else{
            (*((*itJugV)->jugadorObs)).second.dir=(*itJugV) -> dir ; // accedo a la tercera posicion de la tupla para cambiar su direccion en jugadores Observable
            (*((*itJugV)->jugadorObs)).second.pos=(*itJugV) -> pos ; // accedo a la segunda posicion de la tupla para cambiar su posicion en jugadores vivos Observables

			itJugV++;
	    }
	}


}

void ExtremeExorcism::ejecutarAccion(Jugador j, Accion a) {
    vector<dataJ>::iterator punteroJ = jugadoresPorNombre.Significado(j); //significado(jugadoresPorNombre, j)

    if(a == MABAJO || a == MARRIBA || a == MDERECHA || a== MIZQUIERDA) {

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
			(punteroJ->accionesJ)->push_back(Evento(punteroJ->pos,punteroJ->dir,true));
			_habitacion.disparar(true,punteroJ->pos,punteroJ->dir);
			auto itFanV = fantasmasV.begin();
			while(itFanV != fantasmasV.end()){
				if(!_habitacion.estaVivo(false, (*itFanV)->pos)){
					if((*itFanV)->id == _fantasmas.size()-1){
						siguienteRonda(punteroJ);
						return;
					}
					itFanV = fantasmasV.erase(itFanV);
				}else{
					itFanV++;
				}
			}

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
	list<PosYDir> fan;

	for(auto it = fantasmasV.begin();it != fantasmasV.end();it++){
		if((*it)->accionActual == (*it)->accionInicial) {
			if((*it)->accionFinal->dispara == true){
				fan.push_back(PosYDir((*it)->pos,(*it)->dir));
			}
		}else{
			if(prev((*it)->accionActual)->dispara == true){
				fan.push_back(PosYDir((*it)->pos,(*it)->dir));
			}
		}
	}

	return fan;
}

set<Pos> ExtremeExorcism::posicionesDisparadas() const
{
	return set<Pos>();
}

bool ExtremeExorcism::jugadorVivo(Jugador j) const
{
	return jugadoresPorNombre.Significado(j)->vivo;
}

const Habitacion & ExtremeExorcism::habitacion() const
{
	return _habitacion;
}

PosYDir ExtremeExorcism::posicionJugador(Jugador j) const
{
	return PosYDir(jugadoresPorNombre.Significado(j)->pos,jugadoresPorNombre.Significado(j)->dir);
}

const set<Jugador>& ExtremeExorcism::jugadores()
{
	return jugadoresPorNombre.Claves();
}

const list<Fantasma>& ExtremeExorcism::fantasmas() const
{
	return accionesF;
}

const list<Evento>& ExtremeExorcism::acciones(string jug) const
{
	return *jugadoresPorNombre.Significado(jug)->accionesJ;
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
	list<Evento> inv;

	for(Evento accion : acciones){
		inv.push_front(invertir(accion));
	}

	return inv;
}

Evento ExtremeExorcism::invertir(const Evento & evento)
{
	Evento evento_inv = evento;

	if(evento.dir == ARRIBA)
		evento_inv.dir = ABAJO;
	if(evento.dir == ABAJO)
		evento_inv.dir = ARRIBA;
	if(evento.dir == DERECHA)
		evento_inv.dir = IZQUIERDA;
	if(evento.dir == IZQUIERDA)
		evento_inv.dir = DERECHA;

	return evento_inv;
}



void ExtremeExorcism::debug() const{
    cerr << "******************************* ExtremeExorcism ***********************" << endl;
    cerr << "*************jugadoresVivos*************" << endl;
    map<int,string> dir_s = {{ARRIBA,"ARRIBA"},{ABAJO,"ABAJO"},{DERECHA,"DERECHA"},{IZQUIERDA,"IZQUIERDA"}};
    for(auto jv : jugadoresV){
        cerr << "****** Jugador ******" << endl;
        auto j = *jv;
        cerr << "Nombre: " << j.nombre << endl;
        cerr << "Posicion: X " << j.pos.first << " Y " << j.pos.second << endl;
        cerr << "Direccion: " << dir_s[j.dir] << endl;
        cerr << "Vivo: " << (j.vivo ? "Si" : "No")  << endl;
        cerr << "Ultima accion: ";if((*j.accionesJ).size() > 0)cerr << (*j.accionesJ).back();else cerr << "None";cerr << endl;
        cerr << "JugadorObs: Nombre " << (*j.jugadorObs).first << " PosYDir " <<  (*j.jugadorObs).second << endl;
    }

    cerr << "*************fantasmasVivos*************" << endl;
    for(auto fv : fantasmasV){
        cerr << "****** Fantasma ******" << endl;
        auto f = *fv;
        cerr << "ID: " << f.id << endl;
        cerr << "Posicion: X " << f.pos.first << " Y " << f.pos.second << endl;
        cerr << "Direccion: " << dir_s[f.dir] << endl;
        cerr << "AccionActual: " << (*f.accionActual) << endl;
        cerr << "AccionInicial: " << (*f.accionInicial) << endl;
        cerr << "AccionFinal: " << *prev(f.accionFinal) << endl;
    }
    cerr << "**************************************************************************" << endl;
}



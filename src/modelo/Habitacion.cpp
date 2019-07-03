#include "Habitacion.h"
#include "assert.h"
#include <istream>
#include <sstream>
#include <string>

Habitacion string_to_hab(std::istream& is) {
    int row = 0;
    int col = 0;
    int max_col = 0;
    int width;
    int height;

    set<Pos> occupied;

    char c;
    while (is.get(c)) {
        if (c == '#') {
            occupied.insert(Pos(col, row));
            col++;
        } else if (c == '\n') {
            row++;
            max_col = std::max(col, max_col);
            col = 0;
        } else {
            col++;
        }
    }
    width = max_col;
    height = row;

    assert(height == width);

    return Habitacion(height, occupied);
}

Habitacion string_to_hab(string s) {
    std::istringstream is(s);
    int row = 0;
    int col = 0;
    int max_col = 0;
    int width;
    int height;

    set<Pos> occupied;

    char c;
    while (is.get(c)) {
        if (c == '#') {
            occupied.insert(Pos(col, row));
            col++;
        } else if (c == '\n') {
            row++;
            max_col = std::max(col, max_col);
            col = 0;
        } else {
            col++;
        }
    }
    width = max_col;
    height = row;

    assert(height == width);

    return Habitacion(height, occupied);
}

void Habitacion::debug() const{
    cerr << "FANTASMAS" << endl;
    for(int i = 0;i < tamano;i++){
        for(int x = 0;x < tamano;x++){
            cerr << tablero[x][i].fantasmas << " ";
        }
        cerr << endl;
    }
    cerr << "JUGADORES" << endl;
    for(int i = 0;i < tamano;i++){
        for(int x = 0;x < tamano;x++){
            cerr << tablero[x][i].jugadores << " ";
        }
        cerr << endl;
    }
    cerr << "OBSTACULOS" << endl;
    for(int i = 0;i < tamano;i++){
        for(int x = 0;x < tamano;x++){
            cerr << tablero[x][i].obstaculo << " ";
        }
        cerr << endl;
    }
    cerr << "DISPARADOS" << endl;
    for(int i = 0;i < tamano;i++){
        for(int x = 0;x < tamano;x++){
            cerr << tablero[x][i].disparada << " ";
        }
        cerr << endl;
    }
}

Habitacion::Habitacion(unsigned int tam): tamano(tam){
    tablero = new Celda* [tam];
    for(int i = 0;i < tam;i++){
        tablero[i] = new Celda [tam];
    }
}

Habitacion::Habitacion(const Habitacion& h){
    tamano = h.tamano;
    tablero = new Celda* [tamano];
    for(int i = 0;i < tamano;i++){
        tablero[i] = new Celda [tamano];
        for(int x = 0;x < tamano;x++){
            tablero[i][x] = h.tablero[i][x];
        }
    }


}

Habitacion::~Habitacion() {
    for(int i = 0;i < tamano;i++){
        delete[] tablero[i];
    }
    delete[] tablero;
}

void Habitacion::agregarJugadores(const vector<Pos>& jug) {
    for(const Pos& pos:jug){
        tablero[pos.first][pos.second].jugadores++;
    }
}

void Habitacion::agregarFantasmas(const vector<Pos>& fan){
    for(const Pos& pos:fan){
        tablero[pos.first][pos.second].fantasmas++;
    }
}

void Habitacion::agregarObstaculos(const vector<Pos>& obs){
    for(const Pos& pos:obs){
        tablero[pos.first][pos.second].obstaculo = true;
    }
}

bool Habitacion::ocupado(Pos pos) const {
    return tablero[pos.first][pos.second].obstaculo;
}

const linear_set<Pos>& Habitacion::posDisparadasFantasma() const {
    return  pos_disparadas;
}

bool Habitacion::estaVivo(bool jug, Pos pos) const {
    if(jug){
        return tablero[pos.first][pos.second].jugadores != 0;
    } else {
        return tablero[pos.first][pos.second].fantasmas != 0;
    }
}

Pos Habitacion::adyacente(Pos pos, Dir dir) const {
    switch (dir){
        case ARRIBA:
            return Pos(pos.first,pos.second + 1);
        case ABAJO:
            return Pos(pos.first,pos.second - 1);
        case DERECHA:
            return Pos(pos.first + 1,pos.second);
        case IZQUIERDA:
            return Pos(pos.first - 1,pos.second);
    }
}

void Habitacion::disparar(bool jug, Pos pos, Dir dir) {
    Pos pos_actual = adyacente(pos,dir);
    while(iEsPosValida(pos_actual)){
        if(jug){
            tablero[pos_actual.first][pos_actual.second].fantasmas = 0;
        } else{
            if(not(tablero[pos_actual.first][pos_actual.second].disparada)){
                pos_disparadas.insert(pos_actual);
                tablero[pos_actual.first][pos_actual.second].disparada = true;
            }
            tablero[pos_actual.first][pos_actual.second].jugadores = 0;
        }
        pos_actual = adyacente(pos_actual,dir);
    }
}

void Habitacion::mover(bool jug, Pos pos, Dir dir) {
    Pos pos_nueva = adyacente(pos,dir);
    if(jug){
        tablero[pos.first][pos.second].jugadores--;
        tablero[pos_nueva.first][pos_nueva.second].jugadores++;
    } else{
        tablero[pos.first][pos.second].fantasmas--;
        tablero[pos_nueva.first][pos_nueva.second].fantasmas++;
    }
}

bool Habitacion::esMovValido(Pos pos, Dir dir) const {
    return iEsPosValida(adyacente(pos,dir));
}

void Habitacion::resetear() {
    for(int i = 0;i < tamano;i++){
        for (int j = 0; j < tamano; j++) {
            tablero[i][j].resetear();
        }
    }
    pos_disparadas = linear_set<Pos>();
}

unsigned int Habitacion::tam() const {
    return tamano;
}


Habitacion::Habitacion(unsigned int tam, set<Pos> obs): tamano(tam) {
    tablero = new Celda* [tam];
    for(int i = 0;i < tam;i++){
        tablero[i] = new Celda [tam];
    }
    for(Pos p:obs){
        tablero[p.first][p.second] = Celda(true,0,0,false);
    }
}

bool Habitacion::iEsPosValida(Pos pos) const {
    return ((pos.first < tamano) and (pos.second < tamano) and (not(ocupado(pos))));
}

bool Habitacion::operator==(const Habitacion &h) const {
    if(tamano != h.tamano)
        return false;

    for(int i = 0;i < tamano;i++) {
        for (int x = 0; x < tamano; x++) {
            if(tablero[i][x].obstaculo != h.tablero[i][x].obstaculo)
                return false;
        }
    }
    return pos_disparadas == h.pos_disparadas;
};
// Completar

void Habitacion::resetear_turno() {
    pos_disparadas = linear_set<Pos>();

    for(int i = 0;i < tamano;i++){
        for (int j = 0; j < tamano; j++) {
            tablero[i][j].disparada = false;
        }
    }

}
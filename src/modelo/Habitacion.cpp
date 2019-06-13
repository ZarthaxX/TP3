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

// Completar

Habitacion::Habitacion(unsigned int tam, set<Pos> ocupadas)
{
}

unsigned int Habitacion::tam() const
{
	return 0;
}

bool Habitacion::ocupado(Pos) const
{
	return false;
}

bool Habitacion::operator==(const Habitacion &) const
{
	return false;
}

void Habitacion::agregarJugadores(const vector<Pos>& jugadores)
{
}

void Habitacion::agregarFantasmas(const vector<Pos>& fantasmas)
{
}

const set<Pos>& Habitacion::posDisparadasFantasma() const
{
	return set<Pos>();
}

bool Habitacion::estaVivo(bool jug, Pos pos) const
{
	return false;
}

Pos Habitacion::adyacente(Pos pos, Dir dir) const
{
	return Pos();
}

void Habitacion::disparar(bool jug, Pos pos, Dir dir)
{
}

void Habitacion::mover(bool jug, Pos pos, Dir dir)
{
}

bool Habitacion::esMovValido(Pos pos, Dir dir) const
{
	return false;
}

void Habitacion::resetear()
{
}

bool Habitacion::iEsPosValida(Pos pos) const
{
	return false;
}

void Habitacion::agregarObstaculos(const set<Pos>& obstaculos)
{
}

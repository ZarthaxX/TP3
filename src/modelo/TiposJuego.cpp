#include "TiposJuego.h"

Evento Evento::pasar() const {
  Evento e(pos, dir, false);
  return e;
}

PosYDir Evento::pos_y_dir() const {
  PosYDir pd(pos, dir);
  return pd;
}

Evento::Evento(Pos p, Dir d, bool disp) : pos(p), dir(d), dispara(disp) {}

PosYDir::PosYDir() {}

PosYDir::PosYDir(Pos p, Dir d) : pos(p), dir(d) {}


ostream &operator<<(ostream &os, const Evento &e) {
    map<int,string> dir_s = {{ARRIBA,"ARRIBA"},{ABAJO,"ABAJO"},{DERECHA,"DERECHA"},{IZQUIERDA,"IZQUIERDA"}};
  os << "Evento(pos=<" << e.pos.first << ", " << e.pos.second << ">,";
  os << " dir=" << (dir_s.find(e.dir) == dir_s.end() ? "ERROR " : dir_s[e.dir]) << ", " << e.dispara << ")";
  return os;
}

ostream &operator<<(ostream &os, const PosYDir &pd) {
    map<int,string> dir_s = {{ARRIBA,"ARRIBA"},{ABAJO,"ABAJO"},{DERECHA,"DERECHA"},{IZQUIERDA,"IZQUIERDA"}};
  os << "(pos=<" << pd.pos.first << ", " << pd.pos.second << ">,";
  os << " dir=" << (dir_s.find(pd.dir) == dir_s.end() ? "ERROR " : dir_s[pd.dir]) << ")";
  return os;
}

bool PosYDir::operator==(const PosYDir &o) const {
  return pos == o.pos && dir == o.dir;
}

bool Evento::operator==(const Evento &o) const {
  return pos == o.pos && dir == o.dir && dispara == o.dispara;
}


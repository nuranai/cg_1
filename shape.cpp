#include "shape.h"

Coords::Coords(float _x, float _y) {
    x = _x;
    y = _y;
}

Connection::Connection(int _begin, int _end) {
    begin = _begin;
    end = _end;
}

Shape::Shape(int _n, Coords** _coords)
{
// this shape is going to be super sexy
    n = _n;
    ver = _coords;
//    reb = new Connection*[_n];
//    for (int i = 0; i < _n; i++) {
//        Connection temp(i, (i + 1) % _n);
//        reb[i] = &temp;
//    }
//    ver = new Coords();
}

void Shape::SetCoords(int i, float newX, float newY) {
    ver[i]->x = newX;
    ver[i]->y = newY;
}

Shape::~Shape() {
// we are about to destroy a super sexy shape
    for (int i = 0; i < n; i++) {
        delete ver[i];
    }
    delete []ver;
}

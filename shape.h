#ifndef SHAPE_H
#define SHAPE_H
//#include <area.h>

class Shape;

class Coords {
private:
    float x;
    float y;
public:
    Coords(float _x, float _y);
    ~Coords() {};
    float getX() {return x;}
    float getY() {return y;}
    friend class Shape;
};

class Connection {
private:
    int begin;
    int end;
public:
    Connection(int _begin, int _end);
    ~Connection() {};
    friend class Shape;
};

class Shape
{
private:
    Coords **ver;
    int n;
public:
//    Connection **reb;
    Shape(int _n, Coords** _coords);
    ~Shape();
    friend class Area;
    Coords* getCoords(int i) {return ver[i];}
    void SetCoords(int i, float, float);
    int getN() {return n;}
};

#endif // SHAPE_H

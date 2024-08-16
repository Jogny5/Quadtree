#ifndef NODO_H
#define NODO_H
#include "Point.h"
#include <utility>
#include <iostream>

#pragma once

class Nodo
{

public:

    Point punto;
    int poblacion;
    bool color;
    float latitud;
    float longitud;

public:
    Nodo(Point pto, int pob);
    ~Nodo();
    void setColor();
    void setPoblacion(int pob);
    void setLatitud(float lat);
    void setLongitud(float Lon);
    int getPoblacion();
    float getLatitud();
    float getLongitud();
    bool getColor();
    
    

};

#endif
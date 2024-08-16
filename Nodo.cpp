#include "Nodo.h"
#include <iostream>
#include <vector>

using namespace std;

Nodo::Nodo(Point pto, int pob):punto(pto),poblacion(pob)
{

    this->color=false;

}

Nodo::~Nodo()
{

}

void Nodo::setColor(){

    this->color=true;
}

void Nodo::setPoblacion(int pob){

    poblacion=pob;
}

void Nodo::setLatitud(float lat){

    latitud=lat;
}

void Nodo::setLongitud(float lon){

    longitud=lon;
}

int Nodo::getPoblacion(){
    return poblacion;
}

float Nodo::getLatitud(){
    return latitud;
}

float Nodo::getLongitud(){
    return longitud;
}

bool Nodo::getColor(){
    return color;
}

#include "Point.h"
#include <iostream>
#include <vector>

using namespace std;

Point::Point(float x, float y)
{   
    this->coordenadaX = x;
    this->coordenadaY = y;

}

Point::~Point()
{

}

float Point::getX(){
    return coordenadaX;
}

float Point::getY(){
    return coordenadaY;
}

void Point::setX(float x){
    this->coordenadaX=x;
}

void Point::setY(float y){
    this->coordenadaY=y;
}